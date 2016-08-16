#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <execinfo.h>
#include <exception>
#include <stdexcept>
#include "exception.h"

using namespace muduo_test;
using std::string;
using std::cout;
using std::endl;

//complier:
//g++ -rdynamic
//加上了-rdynamic才可以显示符号表中的函数名信息，
//不然只能显示符合表中调用的地址

void Exception::fillStackTrace() {
    const int kBuffsz = 100;
    void *buffer[kBuffsz];
    char **symbolsTrace;
    
    int bufsz = ::backtrace(buffer, kBuffsz);
    if (bufsz <=0) {
        stack_ = "backtrace error";
        return ;
    }
    symbolsTrace = backtrace_symbols(buffer, bufsz);
    
    for (int i = 0; i!=bufsz; ++i) {
        //stack_ += symbolsTrace[i];
        //stack_ += "\n";
        //string.append(string) : append to string
        //string.push_back(char) : append character to string
        stack_.append(symbolsTrace[i]);
        stack_.push_back('\n');
    }
    free(symbolsTrace);
}

void foo(void) {
    cout << __func__ << " begin" << endl;
    throw Exception("foo Exception");
}

void bar(void) {
    try{
        foo();
    }catch(const std::runtime_error &r_err) {
        cout << __func__ << "catch :"
             << r_err.what() << endl;
        throw;
    }catch(const muduo_test::Exception &Excp) {
        cout << __func__ << " catch: " 
             << Excp.what() << endl;
        cout << "And stacktrace: " << endl
             << Excp.stackTrace() << endl;
        throw;
    }
}

int main() {
    try{
        bar();
    }catch(const std::exception &ep) {
        cout << __func__ << " catch :"
             << ep.what() << endl;
    }
    return 0;
}
