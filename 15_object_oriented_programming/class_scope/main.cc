#include <iostream>
#include <string>
#include "base_and_derived.h"

using namespace std;

int main(void) {
    Base bobj; D1 d1obj; D2 d2obj;

    Base &rb1 = bobj, &rb2 = d1obj, &rb3 = d2obj; //reference 

    rb1.fcn();   rb2.fcn();   rb3.fcn();
    cout << "____________________________" << endl;

    D1 &rd1 = d1obj, &rd2 = d2obj;
    //rb2.f2();  failed
    rd1.f2();     rd2.f2();  
    cout << "____________________________" << endl;

    D1 &rd12 = d2obj;   D2 &rd22 = d2obj;
    rd12.fcn(12);   rd22.fcn(12);
    return 0;
}
