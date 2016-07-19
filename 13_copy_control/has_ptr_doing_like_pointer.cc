#include <iostream>
#include <sstream>
#include <string>

using namespace std;
/*
 * 行为像指针的类
 */
class HasPtr {
public:
    HasPtr(const string &s) :
        ps (new string(s)), i(0), use(new size_t(1)) 
        { cout << "HasPtr init " << print_value() << endl; }
    
    HasPtr(const HasPtr &rhs) :
        ps (rhs.ps), i (rhs.i), use(rhs.use) 
        {   ++*use;                                   //关键一步
            cout << "HasPtr copy ctr " << print_value() << endl; }

    HasPtr &operator=(const HasPtr &);

    ~HasPtr() {
        --*use;
        cout << "~HasPtr " << print_value() << endl;
        if (*use == 0) {
            delete ps;
            delete use;
        }
    }
    
private:
    const string print_value() {
        ostringstream ostr;
        ostr << "s:" << *ps << " i:" << i << " use:" << *use ;
        return ostr.str();
    }
    string *ps;
    int i;
    size_t *use;
};

//拷贝赋值运算符会组合析构和拷贝构造函数的工作
HasPtr &
HasPtr::operator=(const HasPtr &rhs) {
    ++*rhs.use;    //这里必须要先++，因为如果是use==1,并且自己赋值给自己的话，use这里就会出现段错误
    --*use;
    cout << "HasPtr operator= delete before " << print_value() << endl; 
    if (*use == 0) { //只有当为0时才可以delete，不为0就只能修改指针指向区域的值
        delete ps;
        delete use;
    }
    use = rhs.use;
    ps = rhs.ps;
    i = rhs.i;
    cout << "HasPtr operator= " << print_value() << endl;
    return *this;
}

int main(void) {
    HasPtr p1("Hello World");
    p1 = p1;
    HasPtr p2(p1);
    p2 = p1;
    return 0;
}
