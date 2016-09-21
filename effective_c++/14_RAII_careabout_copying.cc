#include <iostream>

//在资源管理类(RAII)中小心copying行为
//两种策略
//1.禁止复制 ： : private noncopyable
//或者 类似与auto_ptr只能保证一个auto_ptr拥有资源
//通过赋值之类的方法会使原auto_ptr的资源变为NULL
//
//2.对底层资源使用引用计数法(reference-count) ==> shared_ptr

using namespace std;

class uncopyable {
protected:
    uncopyable() {}
    ~uncopyable() {}
private:
    uncopyable(const uncopyable&);
    uncopyable& operator=(const uncopyable&);
}

class base {
public:
    explicit base(int data) : data_(data) {
        cout << "base default constructor" << endl;
    }

    virtual ~base() {
        cout << "base virtual destructor" << endl;
    }

private:
    int data_;
};



int main() {
    return 0;
}
