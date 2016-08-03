#include "static_obj.h"
#include <iostream>

using namespace std;

int s::a = 0;

s global_s;

void test_local_static_var(void) {
    //显然局部静态变量只有在第一次调用的时候
    //才会初始化
    static s fun_static_s;
    cout << __func__ << endl;

    static_func();
}

static void static_func(void) {
    static s static_s;
    cout << __func__ << endl;
}
//如果将static function放在.c文件中
//那么就只能在该文件中使用此静态函数
//
//但是放入了.h文件中，只要是include了
//该函数，都可以调用
