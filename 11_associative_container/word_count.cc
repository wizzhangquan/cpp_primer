#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <iterator>

/*
 * 统计出现的单词数目
 *
 * 这里我使用了istream_iterator(iostream迭代器)=> *fin_iter++
 * 并使用了set来排除常用的单词。
 */

using namespace std;

set<string> exclude = {"the", "but", "and", "or", "an", "a", "is", "are"
                       "The", "But", "And", "Or", "An", "A", "Is", "are"};

void word_cnt(const char *filename, map<string, size_t> &words, set<string> &excl = exclude) {
    fstream fin(filename, ifstream::in);
    if (!fin.is_open()) {
        cout << "Error open file" << endl;
        exit(1);
    }
    
    istream_iterator<string> fin_iter(fin), eof;
    while (fin_iter != eof) {
        if (excl.find(*fin_iter) == excl.end())
            ++words.insert({*fin_iter++, 0}).first->second;
        else
            ++fin_iter;
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
