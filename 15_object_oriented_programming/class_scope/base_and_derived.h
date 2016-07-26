#ifndef _BASE_AND_DERIVED_H__
#define _BASE_AND_DERIVED_H__

#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    virtual void fcn() { cout << "Base's fcn(void)" << endl; }
};

class D1 : public Base {
public:
    void fcn(int i = 0) { cout << "D1's fcn(int)" << endl; }
    virtual void f2() { cout << "D1's f2" << endl; }
};

class D2 : public D1 {
public:
    void fcn() { cout << "D2's fcn(void)" << endl; }

    void fcn(int i = 0) { cout << "D2's fcn(int)" << endl; }

    void f2() { cout << "D2's f2" << endl; }
};

#endif
