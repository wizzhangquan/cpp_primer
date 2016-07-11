#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

/*
 * 重排并删除重复单词
 */


void print_vector(vector<string>::const_iterator begin, vector<string>::const_iterator end) {
    for (auto iter = begin; iter != end; ++iter)
        cout << *iter << "  ";
    cout << endl;
}

void elim_dups(vector<string> &words) {
    sort(words.begin(), words.end());
    cout << "sort : " ;
    print_vector(words.begin(), words.end());
 
    cout << "unique : ";
    auto end_unique = unique(words.begin(), words.end());
    print_vector(words.begin(), words.end());

    cout << "erase : ";
    words.erase(end_unique, words.end());
    print_vector(words.begin(), words.end());
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: ./a.out words" << endl;
        exit(1);
    }

    ifstream fin(argv[1], ifstream::in);
    string word;
    vector<string> words;

    while (fin >> word)
        words.push_back(word);
    fin.close();

    cout << "words : " ;
    print_vector(words.begin(),words.end());
    
    elim_dups(words);
    return 0;
}
