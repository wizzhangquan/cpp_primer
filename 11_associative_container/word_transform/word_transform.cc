#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>

/*
 * 通过阅读abbreviation.txt来讲单词转换
 * 把文本的缩写展开
 */

using namespace std;

const map<string, string> build_addreviation_map(ifstream &map_file) {
    map<string, string> trans_map;
    string key;
    string value;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw runtime_error("no rule for " + key);
    }
    
    /*
    cout << "print map_file : " <<endl;
    for (auto kv : trans_map)
        cout << kv.first << " : " << kv.second << endl;
    */
    return trans_map;
}

const string &trans_word(const map<string, string> &trans_map, const string &word) {
    auto iter_find = trans_map.find(word);
    if (iter_find == trans_map.end())
        return word;
    else
        return iter_find->second;
        //return trans_map[word];  因为这里的trans_map是const，如果使用[]/at会导致map改变，故而只能使用find
}

void print_eassy_transform(const char *eassy_name, const char *transfile_name) {
    ifstream transfile(transfile_name, ifstream::in);
    ifstream eassy(eassy_name, ifstream::in);
    if (!transfile.is_open() || !eassy.is_open()) {
        cout << "Error open file" << endl;
        exit(1);
    }
    
    const map<string, string> &trans_map = build_addreviation_map(transfile);
    string line;
    while (getline(eassy, line)) {
        istringstream istr(line);
        string word;
        while (istr >> word)
            cout << trans_word(trans_map, word) << " " ;
        cout << endl;
    } 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "usage : ./a.out eassy.txt trans.txt" << endl;
        exit(1);
    }
    print_eassy_transform(argv[1], argv[2]);
    return 0;
}
