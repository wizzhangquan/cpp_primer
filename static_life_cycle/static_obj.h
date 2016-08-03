#pragma once
#ifndef _STATIC_OBJ_H__
#define _STATIC_OBJ_H__

#include <iostream>

using namespace std;

class s {
public:
    s()  {
        ++a; 
        cout << "s construct" 
             << " a:" << a << endl; 
    }
    ~s() {
        cout << "s destruct"
             << " a:" << a << endl;
        --a;
    }

    static void f() {
        cout << "s static f" << endl;
    }
private:
    static int a;
};

//然而，static function也可以在头文件中
//提前声明，注意声明和定义都要加static
static void static_func(void);

void test_local_static_var(void);
#endif
