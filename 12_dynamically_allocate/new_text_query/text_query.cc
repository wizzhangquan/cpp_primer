#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "text_query.h"

using namespace std;

int err_out(const string &err_cause) {
    cout << err_cause << endl;
    exit(1);
}

TextQuery::TextQuery(ifstream &infile) {
    if ( ! infile.is_open()) err_out("error open file");

    file = new vector<string>;
    word_map = new word_map_type;

    string line;
    line_no n = 0;
    while (getline(infile, line)) {
        file->push_back(line);
        insert_word_a_line(line, n);
        ++n;
    } 
}

void
TextQuery::insert_word_a_line(const string &line, line_no n) {
    istringstream istr(line);
    string word;
    while (istr >> word) {
        auto &line_set = (*word_map)[word];
        if (line_set == NULL)
            line_set = new set<line_no>;
        line_set->insert(n);
        
        cout << word <<" in lines: ";
        for_each(line_set->begin(), line_set->end(),
                 [] (const line_no no) -> void 
                 {cout <<no<<" "; });
        /*
        cout << word << " in lines : ";
        for (auto &no : *line_set)
            cout << no << " ";
        */
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2)
        err_out("usage: ./a.out text.txt");
    ifstream infile(argv[1]);
    TextQuery tq(infile);
    infile.close();
    return 0;
}
