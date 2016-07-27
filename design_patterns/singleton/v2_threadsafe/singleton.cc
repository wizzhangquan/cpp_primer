#include <iostream>
#include <pthread.h>

using namespace std;

class Singleton {
public:

    static Singleton *getInstance();
    static void destory();
    void doSomething() { cout << "Singleton Instance do something" << endl; }

private:
    Singleton() { }
    ~Singleton() { }
    Singleton(const Singleton&) = delete;
    Singleton &operator=(const Singleton&) = delete;

    static Singleton *instance;

    static pthread_mutex_t mlock;
};

Singleton * Singleton::instance = NULL;

pthread_mutex_t 
Singleton::mlock = PTHREAD_MUTEX_INITIALIZER;

Singleton *
Singleton::getInstance() {
    if (instance == NULL) {
        pthread_mutex_lock(&mlock);
        if (instance == NULL) {
            instance = new Singleton();
        }
        pthread_mutex_unlock(&mlock);
    }
    return instance;
}

void
Singleton::destory() {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
    cout << "Singleton destory" << endl;
}

int main() {
    Singleton *singletonObj = Singleton::getInstance();
    singletonObj->doSomething();
    Singleton::destory();

    return 0;
}
