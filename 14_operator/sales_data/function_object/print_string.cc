#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class PrintSting {
public:
    PrintSting(ostream &o = cout, char c = ' ') :
        os(o), sep(c) { }
    void operator()(const string &s) const { os << s << sep; }
private:
    ostream &os;
    char sep;
};

int main(void) {
    PrintSting printer(cout, '#');
    vector< string > sv;
    sv.push_back("hello");
    sv.push_back("world");
    sv.push_back("lala");
    for_each(sv.begin(), sv.end(), printer);
    cout << endl;
    sort(sv.begin(), sv.end(), 
        [] (string a, string b) { return &a < &b;});
     /*
    int i = 0, s = 42;
    int *a = &i, *b = &s;
    cout << (a < b);
    */
    return 0;
}
