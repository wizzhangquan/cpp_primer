#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

/*
 * test : back_inserter, front_inserter, inserter
 *
 * using three inserters to get unique_copy
 *
 * 另外如果文本内容为数字，但我们这里是使用string来排序的，
 * 那么会导致使用字符大小来排序并不是按照数字值 例如 str(11) < str(2)
 */

#define TITLE_WIDTH 18
#define TITLE_TALL " : "
template<typename Sequence>
void show_container(Sequence const& seq, const char *title = NULL) {
    if (title != NULL) {
        cout.width(TITLE_WIDTH);
        cout << title << TITLE_TALL;
    }
    for_each(begin(seq), end(seq),
        [](const string &str){ cout << str <<" "; });
    cout << endl;
}

template<typename Sequence>
void read_from_file(const char *filename, Sequence &words) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error open file" << endl;
        exit(1);
    }
    
    string word;
    while (fin >> word)
        words.push_back(word);
    fin.close();
}

template<typename Sequence>
void show_unique_copy(Sequence &words) {
    sort(words.begin(), words.end());

    list<string> repeated_dups_back;
    unique_copy(words.begin(), words.end(),
        back_inserter(repeated_dups_back));
    show_container(words, "after unique_copy");
    show_container(repeated_dups_back, "back_inserter");

    list<string> repeated_dups_front;
    unique_copy(words.begin(), words.end(),
        front_inserter(repeated_dups_front));
    show_container(repeated_dups_front, "front_inserter");

    list<string> repeated_dups;
    unique_copy(words.begin(), words.end(),
            inserter(repeated_dups, repeated_dups.end())); //这里使用.begin(), end()效果是一样的.
    show_container(repeated_dups, "inserter");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage : ./a.out words.txt/insert_example.txt" << endl;
        exit(1);
    }
    
    vector<string> words;
    read_from_file(argv[1], words);
    show_container(words, "original");
    show_unique_copy(words);
    return 0;
}
