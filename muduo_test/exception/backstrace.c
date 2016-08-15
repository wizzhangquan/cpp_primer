#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define BUFSZ 100

//测试backtrace函数
//以及backtrace_symbol函数
//cc -rdynamic 

void test_backtrace() {
    void *buffer[BUFSZ];
    char ** func_symbols;
    int i;
    int back_sz = backtrace(buffer, BUFSZ);

    func_symbols = backtrace_symbols(buffer, back_sz);
    for (i=0; i<back_sz; ++i) {
        printf("%s\n", func_symbols[i]);
    }
    free(func_symbols);
    return ;
}

void func1() {
    test_backtrace();
}

void func2() {
    func1();
}

void func3() {
    func2();
}

int main() {
    func3();
    return 0;
}
