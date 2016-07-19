#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class HasPtr {
public:
    HasPtr(const string &s = string()) : 
        ps (new string(s)), i (0) {}

    HasPtr(const HasPtr &p) :
        ps (new string(*p.ps)), i (p.i) {}
    
    HasPtr &operator=(const HasPtr &);
    ~HasPtr() { delete ps; };
private:
    string *ps;
    int i;
};

HasPtr &
HasPtr:: operator=(const HasPtr &rhs) { //大多数赋值运算符组合了析构函数和拷贝构造函数的工作
    string *newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}

int main() {
    HasPtr p("hello world");
    p = p;
    return 0;
}
