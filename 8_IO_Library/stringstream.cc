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
        record.str(readLine);
        info.read(record);
        people.push_back(info);     
        record.clear();                // 当我们阅读完一行之后,record对象的状态就为fail | eof,
                                       // 那么之后再使用之就无法读取或写入字符了
    }

    for (const auto &entry : people)
        entry.print(cout);
    
    return 0;
}
