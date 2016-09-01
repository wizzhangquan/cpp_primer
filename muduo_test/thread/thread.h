#ifndef _MUDUO_TEST_THREAD_THREAD_H_
#define _MUDUO_TEST_THREAD_THREAD_H_

#include <pthread.h>
#include <string>
#include <memory>
#include <functional>
#include "../atomic/atomic.h"

using namespace std;

namespace muduo_test {

class Thread {
public:
    typedef std::function<void (void)> threadFunc;
    
    explicit Thread(const threadFunc func, const string &name = string());
    ~Thread(); //pthread detach
    void start();
    int join();

    bool started() { 
        return started_; 
    }
    bool joined() {
        return joined_;
    }
    const string name() const {
        return name_;
    }
    const pthread_t pthreadId() const {
        return pthreadId_;
    }
    pid_t tid() const {
        return *tid_;
    }

    static const int numCreated() {
        return threadNum_.get();
    }
private:
    threadFunc func_;
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    std::shared_ptr<pid_t> tid_;
    string name_;

    static AtomicInt32 threadNum_;
};//Thread

}//muduo_test

#endif
