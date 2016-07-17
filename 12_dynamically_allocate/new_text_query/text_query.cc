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

TextQuery::~TextQuery() {
    file->clear();
    delete file;
    
    for (auto i = word_map->begin();
        i != word_map->end(); ) {
        delete i->second;
        i = word_map->erase(i);
    }
    cout << "~TextQuery end" << endl;
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
        /*
        cout << word <<" in lines: ";
        for_each(line_set->begin(), line_set->end(),
                 [] (const line_no no) -> void 
                 {cout <<no<<" "; });
        
        cout << word << " in lines : ";
        for (auto &no : *line_set)
            cout << no << " ";
        */
        //cout << endl;
    }
    //cout << endl;
}

QueryResult
TextQuery::query(const string &sought) const {
    auto loc = word_map->find(sought);
    if (loc == word_map->end())
        return QueryResult(sought, file, NULL);
    else 
        return QueryResult(sought, file, loc->second);
}

ostream &print(ostream &out, const QueryResult &qr) {
    if (qr.lines == NULL)
        return out << qr.sought_word << " occurs 0 times" << endl;
 
    TextQuery::line_no line_cnt = qr.lines->size();
    out << qr.sought_word << " occurs " << line_cnt << " times" << endl;
    for (auto &l : *(qr.lines)) 
        out << "(line " << l << " ) " << qr.file->at(l) << endl;
    return out;
}

void run_queries(std::ifstream &infile) {
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q! to quit: ";
        string sought_word;
        if (!(cin >> sought_word) || sought_word == "q!") break;
        
        print(cout, tq.query(sought_word)) << endl;
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2)
        err_out("usage: ./a.out text.txt");
    ifstream infile(argv[1]);
    run_queries(infile);
    infile.close();
    return 0;
}
