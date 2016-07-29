#include <iostream>

using namespace std;

/*
 * use RAII to GC
 */

class Singleton{
public:
    static Singleton *getInstance() {
        return instance;
    }

    int doSomething() {
        ++m_test;
        cout << "Singleton doSomething, test:" 
             << m_test << endl;
    }
private:
    Singleton() {
        m_test = 0;
        cout << "Singleton constructor ,test:" 
             << m_test << endl; }

    ~Singleton() { 
        cout << "Singleton destructor, test:"
              << m_test << endl; }

    Singleton(const Singleton &) = delete;

    Singleton & operator=(const Singleton&) = delete;

    int m_test;

    static Singleton *instance; 

    class GC { //gc只能访问静态变量
    public:
        GC() { 
            cout << "Singleton inner class GC constructor" << endl; }
        
        ~GC() { 
            if (instance != NULL) {
                delete instance;
                instance = NULL;
                cout << "GC delete instance" << endl;
            }
            cout << "Singleton inner class GC destructor" << endl; 
        }
    };
    static GC gc;  
    //因为是静态变量 所以当整个程序结束的时候会自动的析构
    //那么 就可以在此析构函数中释放各种资源 这里只有instance
    //但也可以有 一些文件锁/文件句柄/数据库连接等等，这些随着
    //程序的关闭而不会立即关闭的资源必须要手动释放 ，于是可以
    //放入在~GC()中进行以上操作

};

Singleton * Singleton::instance = new Singleton();
Singleton::GC Singleton::gc;

int main() {
    
    Singleton *sobj = Singleton::getInstance();
    sobj->doSomething();    
    cout << "===============" << endl;
    sobj->doSomething();
    return 0;
}
