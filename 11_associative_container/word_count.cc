#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <iterator>

/*
 * 统计出现的单词数目
 */

using namespace std;

void word_cnt(const char *filename, map<string, size_t> &words) {
    fstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error open file" << endl;
        exit(1);
    }
    
    istream_iterator<string> fin_iter(fin), eof;
    while (fin_iter != eof) {
        ++words.insert({*fin_iter++, 0}).first->second;
    }
    fin.close();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage : ./a.out example.txt" << endl;
        exit(1);
    }

    map<string, size_t> words;
    word_cnt(argv[1], words);
    
    for (auto w : words)
        cout << w.first << " : " << w.second << endl;
    return 0;
}
