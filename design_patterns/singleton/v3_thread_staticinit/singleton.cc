#include <iostream>

/*
 * 因为静态初始化在程序开始时，也就是进入main函数之前
 * ，那么这样静态初始化实例就保证了线程安全。
 * 在性能要求比较高的时候就可以使用这种方式，从而避免频繁的加锁解锁造成的资源浪费。
 */

using namespace std;

class Singleton {
public:
    static Singleton *getInstance() {
        return const_cast<Singleton *>(instance);    
    }

    static void destory() {
        if (instance != NULL) {
            delete instance;
            instance = NULL;
        }
    }
    
    void doSomething() {
        cout << "Singleton doSomething" << endl;
    } 
private:
    Singleton() { cout << "Singleton constructor" << endl; }
    ~Singleton() { cout << "Singleton destructor" << endl; }

    Singleton(const Singleton&) = delete;
    Singleton & operator=(const Singleton&) = delete;

    static const Singleton *instance; //const
};

const Singleton* Singleton::instance = new Singleton();

int main() {
    Singleton *sObj = Singleton::getInstance();
    sObj->doSomething();
    Singleton::destory();
    return 0;
}
