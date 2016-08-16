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
        stack_ += symbolsTrace[i];
        stack_ += "/n";
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
    }catch(const Exception &Excp) {
        cout << __func__ << " catch: " 
             <<Excp.what() << endl;
        cout << "And stacktrace: " << endl
             << Excp.stackTrace() << end;
    }
}

int main() {
    return 0;
}