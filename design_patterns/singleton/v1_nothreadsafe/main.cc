#include <iostream>
#include "singleton.h"

using namespace std;

int main() {
    Singleton *ins = Singleton::getInstance();
    ins->doSomething();
    return 0;
}
