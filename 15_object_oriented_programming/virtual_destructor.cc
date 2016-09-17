#include <iostream>
#include <memory>

using namespace std;

class base {
public:
    base() {cout << "Base constructor" << endl;}
    virtual ~base() {cout << "Base destructor" << endl;}
};

class derived : public base {
public:
    derived() {cout << "Derived constructor" << endl;}
    virtual ~derived() {cout << "Derived destructor" << endl;}
};

class A {
public:
    A() : data_(0) {cout << "default constructor , data:" << data_ << endl;}
    A(const int d = 0) : data_(d) { cout << "construtor , data:" << data_ << endl;}
    //explicit : A a = 1; //这里就会报错
    A(const A &a) : data_(a.data_) { cout << "copy construtor, data:" << data_ << endl;}
private:
    int data_; 
};

void f(A a) {
    cout << __func__ << endl;
}

int main() {
    //shared_ptr<base> p(new derived());
    //shared_ptr<derived> p = new derived(); ===>ERROR
    //shared_ptr 的接受指针参数的智能指针构造函数是explicit，
    //因此我们不能将一个内置指针隐式转换为一个智能指针
    //必须使用直接初始化形式
    //A a = 1;
    f(1);
    return 0;
}
