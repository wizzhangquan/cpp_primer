#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class PersonInfo {
public:
    PersonInfo() = default;
    
    PersonInfo &read(istream &);
    const PersonInfo &print(ostream &) const;
private:
    string name; 
    vector<string> phones;
};

PersonInfo &
PersonInfo:: read(istream &in) {
    string phoneNumber;

    in >> name;
    while (in >> phoneNumber)
        phones.push_back(phoneNumber);
    return *this;
}

const PersonInfo &
PersonInfo:: print(ostream &out) const{
    out << "Name: " << name 
        << " phones:";
    for (const auto &nums : phones)
        out << " " << nums ;
    out << endl;
}

string format_stream_state(const istream &s) {
    string states = "states :";
    states += "  badbit "  + string(s.bad()  ? "1" : "0");
    states += "  failbit " + string(s.fail() ? "1" : "0");
    states += "  eofbit "  + string(s.eof()  ? "1" : "0");
    states += "  goodbit " + string(s.good() ? "1" : "0");
    return states;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "usage : ./a.out file.txt" << endl;
        return 1;
    }

    ifstream fileIn(argv[1]);
    string readLine;
    istringstream record;
    vector<PersonInfo> people;
    while (getline(fileIn, readLine)) {
        PersonInfo info;
        cout << "Before read " 
             << format_stream_state(record) << endl;
        record.str(readLine);
        info.read(record);
        cout << "After read " 
             << format_stream_state(record) << endl;
        people.push_back(info);     
        record.clear();                // 当我们阅读完一行之后,record对象的状态就为fail | eof,
                                       // 那么由于流一旦发生错误，其上后续的IO操作都会失败
                                       // 再使用之就无法读取或写入字符了
    }

    for (const auto &entry : people)
        entry.print(cout);
    
    return 0;
}
