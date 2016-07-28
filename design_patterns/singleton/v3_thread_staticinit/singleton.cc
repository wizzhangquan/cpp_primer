#include <iostream>

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
