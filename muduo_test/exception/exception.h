#ifndef _MUDUO_TEST_EXCEPTION_H_
#define _MUDUO_TEST_EXCEPTION_H_

#include <string>

namespace muduo_test {

class Exception {
public:
    explicit Exception(const char *what) : message_(what) {
        fillStackTrace();
    }
    explicit Exception(const std::string &what) : message_(what) {
        fillStackTrace();
    }

    const char *what() {
        return message_.c_str();
    }
    
    const char *stackTrace() {
        return stack_.c_str();
    }
private:
    void fillStackTrace();

    std::string message_;
    std::string stack_;
};

}
#endif
