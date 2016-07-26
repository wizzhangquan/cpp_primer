#include <iostream>
#include "singleton.h"

using std::cout;
using std::endl;

Singleton *
Singleton::instance = NULL;

Singleton::Singleton() {
    cout << __func__ << endl;
}

Singleton::~Singleton() {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
    cout << __func__ << endl;
}

//need multi_mutex_lock/unlock
Singleton*
Singleton::getInstance() {
    Singleton *ret = instance;
    if (ret == NULL) {
        instance = new Singleton();
        ret = instance;
    }
    return ret;
}

void
Singleton::doSomething() {
    cout << __func__ << endl;
}

void
Singleton::destroy() {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
    cout << __func__ << endl;
}
