#ifndef _MUDUO_TEST_EXCEPTION_H_
#define _MUDUO_TEST_EXCEPTION_H_

#include <string>
#include <exception>

namespace muduo_test {

class Exception : public std::exception {
public:
    explicit Exception(const char *what) : message_(what) {
        fillStackTrace();
    }
    explicit Exception(const std::string &what) : message_(what) {
        fillStackTrace();
    }

    Exception(const Exception& that) : 
        message_(that.message_), stack_(that.stack_) {
    }

    ~Exception() throw() { //这里的throw()是表示承诺不会抛出异常
        //但在C++11中，是以noexcept来表示不会抛出异常的，
        //新的标准中，throw()已经弃用

    }

    virtual const char *what() {
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
