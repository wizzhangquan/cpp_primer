#include <iostream>
#include <string>

using namespace std;
/*
 * 定义行为像值的类
 * 在 operator= 中使用swap => 于是天然就是异常安全的
 */
class HasPtr {
public:
    friend void swap(HasPtr &, HasPtr &);
    HasPtr(const string &s = string()) :
        ps (new string(s)), i (0) 
        { cout << "init ps:" << *ps << " i:" << i 
               << " addr:" << this << endl; }

    HasPtr(const HasPtr &p) :
        ps (new string(*p.ps)), i(p.i) 
        { cout << "copy cst ps:" << *ps << " i:" << i
               << " addr:" << this << " p's addr:" << &p << endl; }

    HasPtr &operator=(HasPtr); //注意这里不是引用
    ~HasPtr() { cout << "~HasPtr addr:" << this << endl; delete ps; }
private:
    string *ps;
    int i;
};

inline
void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    cout << "swap lhs'addr:" << &lhs << " rhs'addr:" << &rhs << endl;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

HasPtr &
HasPtr::operator=(HasPtr rhs) {
    cout << "operator = this addr:" << this << " rhs'addr:" << &rhs << endl; 
    swap(*this, rhs);
    cout << "operator = after ps:" << *ps << " i:" << i << endl;
    return *this;
}

int main(void) {
    HasPtr p("HelloWorld");
    HasPtr q("heihei");
    q = p;
    return 0;
}
