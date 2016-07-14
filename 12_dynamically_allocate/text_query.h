#ifndef __TEXT_QUERY_H_
#define __TEXT_QUERY_H_

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <utility>

using std::map;
using std::vector;
using std::string;

class Text_lines { //存储文本每行
public :
    Text_lines() = default;
    Text_lines(const string &filename);
    const Text_lines &read_file(const string &filename);
    const string get_line(int num);
    const int lines_cnt();
    
private :
    vector<string> lines;
};

class Text_query {
public :
    Text_query() = default;
    const map<int, int>
        query_every_line(Text_lines &filelines, const string &word);
    const string format_query_result(Text_lines &filelines, const string &word);
private :
    int query_a_line(const string &line);

    map<int, int> occur_nums_of_line; //<line_num, word_cnt>
    string query_word;
};

#endif
