#include <iostream>
/*
 * 这里将成员变量修改为非指针类型
 * 那么在退出的时候就可以调用析构函数，
 * 而不需要编写一个destory的函数来显示销毁变量
 *
 */

using namespace std;

class Singleton {
public:

    static Singleton *getInstance() {
        return &instance;
    }

    void doSomething() {
        ++m_test;
        cout << "Singleton doSomething, test:"
             << m_test << endl;
    }

private:
    
    Singleton() { 
        m_test = 1;
        cout << "Singleton constructor" 
             << " test:" << m_test << endl; 
    }

    ~Singleton() { cout << "Singleton destructor test:" << m_test << endl; }

    Singleton(const Singleton &) = delete;
    Singleton & operator= (const Singleton&) = delete;

    static Singleton instance;
    int m_test; 
};

Singleton Singleton::instance;

int main() {
    Singleton *sobj = Singleton::getInstance();
    sobj->doSomething();

    sobj = Singleton::getInstance();
    sobj->doSomething(); 
    return 0;
}
