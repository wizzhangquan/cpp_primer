#include <iostream>

using namespace std;

class Singleton {
public:
    static Singleton *getInstance() {
        static Singleton instance;
        return &instance;
    }

/***
 *  static Singleton& getInstance() {
 *      static Singleton instance;
 *      return instance;
 *  }
 *  这样写也是可以的。
 *  但是注意：在使用该返回时，不能赋予auto类型
 *  因为会转换为Singleton来接收getInstance()返回值
 *  那么将会调用private: Singleton(const Singleton&) = delete
 *
 *  auto &sobj = Singleton::getInstance(); //is right
 * */

    void doSomething() {
        m_test++;
        cout << "Singleton dosomething, test:"
             << m_test << endl;
    }
private:
    Singleton() { 
        m_test = 1;
        cout << "Singleton constructor, test:" 
             << m_test << endl;
    }

    ~Singleton() { cout << "Singleton destructor, test:" << m_test << endl; }

    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

    int m_test;
};

int fun_test(void) {
    Singleton *sObj = Singleton::getInstance();
    sObj->doSomething();

    cout << "======================" << endl;

    sObj = Singleton::getInstance();
    sObj->doSomething();
 
}

int main(void) {
    fun_test();
    cout << "fun end" << endl;
    return 0;
}
