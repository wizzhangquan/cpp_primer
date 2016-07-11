#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
 
/*
 * biggest: 求大于等于一个给定长度的单词有多少。
 * 并使程序只打印大于等于给定长度的单词 
 */

using namespace std;

#define TITLE_WIDTH 18

void show_strs(const vector<string> &words, const char *title = NULL) {
    cout.width(TITLE_WIDTH);
    if (title != NULL) 
        cout << title << " : ";
    for (auto w : words)
        cout << w << " ";
    cout << endl;
}

void elim_dups(vector<string> &words) {
    sort(words.begin(), words.end());
 
    auto end_unique = unique(words.begin(), words.end());

    words.erase(end_unique, words.end());
}

void bigges(vector<string> &words,
            vector<string>::size_type sz) {
    elim_dups(words);
    show_strs(words, "elim_dups");
    
    stable_sort(words.begin(), words.end(),
        [] (const string &str1,
            const string &str2) -> bool
            {return str1.size() > str2.size();});
    show_strs(words, "stable_sort_by_sz");

    auto iter_first_short = find_if(words.begin(),
                                words.end(),
                        [sz](const string &str) -> bool
                             {return str.size() < sz;});
    int enough_cnt = iter_first_short - words.begin();
    cout.width(TITLE_WIDTH);
    cout << "enough count" << " : " << enough_cnt << endl;
    
    cout.width(TITLE_WIDTH);
    cout << "enough sz " << " : ";
    for_each(words.begin(), iter_first_short,
            [](const string &str) ->void {cout << str << " ";});
    cout << endl;
}

void read_from_file(const char *filename, vector<string> &words) {
    ifstream fin (filename);
    string w;
    while (fin >> w)
        words.push_back(w);
    fin.close();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: ./a.out words.txt" << endl;
        exit(1);
    }

    vector<string> words;
    read_from_file(argv[1], words);
    show_strs(words, "read_from_file"); 
    bigges(words, 4);
    return 0;
}
