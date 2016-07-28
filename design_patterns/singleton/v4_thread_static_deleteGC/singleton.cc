#include <iostream>

using namespace std;

class Singleton {
public:
    static Singleton *getInstance() {
        static Singleton instance;
        return &instance;
    }

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
