#include <iostream>
#include <string>
#include <sstream>

using namespace std;
/*
 * 行为像值的类 ： 即拷贝/赋值都是新的string，两个对象指向的不会是同一个string
 */
class HasPtr {
public:
    HasPtr(const string &s = string()) : 
        ps (new string(s)), i (0) 
        { cout << "HasPtr init s:" << print_value() << endl; }

    HasPtr(const HasPtr &p) :
        ps (new string(*p.ps)), i (p.i) 
        { cout << "HasPtr copy ctr " << print_value() << endl;}
    
    HasPtr &operator=(const HasPtr &);
    ~HasPtr() { delete ps; }
private:
    const string print_value() {
        ostringstream ostr;
        ostr << "s:" << *ps << " i:" << i;
        return ostr.str();
    }
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
