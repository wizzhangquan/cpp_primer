#include <iostream>
#include <string>
#include "base_and_derived.h"

using namespace std;

int main(void) {
    Base bobj; D1 d1obj; D2 d2obj;

    Base &rb1 = bobj, &rb2 = d1obj, &rb3 = d2obj; //reference 

    rb1.fcn();   rb2.fcn();   rb3.fcn();

    return 0;
}
