#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include "exception.h"

using namespace muduo_test;
using std::string;

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

int main() {
    return 0;
}
