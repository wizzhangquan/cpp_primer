#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <exception>
#include <iterator>
#include <utility>
#include "text_query.h"

using namespace std;

int err_out(const string &err_cause) {
    cout << err_cause << endl;
    exit(1);
}

//-----------Text_lines----------------
Text_lines::Text_lines(const string &filename) {
    ifstream file(filename);
    if ( ! file.is_open() ) 
        err_out("error open file");
    
    string line;
    while (getline(file, line))
        lines.push_back(line);
    file.close();
}

const Text_lines &
Text_lines::read_file(const string &filename) {
    if (lines.empty())
        lines.clear();
    
    ifstream file(filename);
    if ( ! file.is_open() ) 
        err_out("error open file");
    
    string line;
    while (getline(file, line))
        lines.push_back(line);
    file.close();
    
    return *this;
}

const int
Text_lines::lines_cnt() {
    return lines.size();
}

const string 
Text_lines::get_line(int num) {
    if (num < 0 || num >= lines_cnt())
        return string();
    return lines.at(num);
}

void Unit_test_Textlines(Text_lines &filelines) {
    int linecnt = filelines.lines_cnt();
    for (int l = 0; l < linecnt; ++l)
        cout << filelines.get_line(l) << endl;
    cout << "line cnt : " << linecnt << endl;
    cout << filelines.get_line( linecnt + 2) << endl;
}

//-----------Text_query-------------------
int
Text_query::query_a_line(const string &line) {
    istringstream istr(line);
    istream_iterator<string> istr_iter(istr), istr_eof;
    
    multiset<string> lineset(istr_iter, istr_eof);
    return lineset.count(query_word);
}

const map<int, int> 
Text_query::query_every_line(Text_lines &filelines, const string &word) {
    if (occur_nums_of_line.size() != 0)
        occur_nums_of_line.empty();
    if (filelines.lines_cnt() == 0) return occur_nums_of_line;

    this->query_word = word;
    string line;
    int filelines_cnt = filelines.lines_cnt();
    for (int line_no = 0; line_no < filelines_cnt; ++line_no) {
        int cnt = query_a_line(filelines.get_line(line_no));
        if (cnt == 0) 
            continue;
        else
            occur_nums_of_line.insert({line_no, cnt});
    }
    return occur_nums_of_line;
}

const string
Text_query::format_query_result(Text_lines &filelines, const string &word) {
    this->query_every_line(filelines, word);
    ostringstream ostr;
    ostr << word << " occurs " << this->occur_nums_of_line.size() 
         << " times" <<endl;
    for (auto line_cnt : this->occur_nums_of_line) {
        ostr << "(line " << line_cnt.first << ") "
             << filelines.get_line(line_cnt.first) << endl;
        //cout << "(line " << line_cnt.first << ") "
        //     << filelines.get_line(line_cnt.first) << endl;
    }
    return ostr.str();
}
int main(int argc, char *argv[]) {
    if (argc != 3)
        err_out("usage: ./a.out text.txt query_word");

    Text_lines filelines(argv[1]);
    Text_query query;
    cout << query.format_query_result(filelines, argv[2]) << endl;
    return 0;
}
