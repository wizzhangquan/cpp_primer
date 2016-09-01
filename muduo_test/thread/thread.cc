#include "currentThread.h"
#include "thread.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <assert.h>

//complier : gcc -std=c++11 -lpthread

using std::shared_ptr;

namespace muduo_test {

namespace current_thread {
    __thread int t_cachedTid;
    __thread char t_tidString[32];
    __thread int t_tidStringLength;
    __thread const char *t_tidname = "unknown";
    
    bool isMainThread() {
        return tid() == ::getpid();
    }
}//current_thread

namespace detail {

int gettid() {
    return ::syscall(SYS_gettid);
}

void afterfork(void) {
    current_thread::t_cachedTid = 0;
    current_thread::t_tidname = "main";
    current_thread::tid();
}

class ThreadNameInitializer {
public:
    ThreadNameInitializer() {
        current_thread::tid();
        current_thread::t_tidname = "main";
        pthread_atfork(NULL, NULL, &afterfork);
    }
};

ThreadNameInitializer init; //before main func

struct ThreadData {
    Thread::threadFunc Func;
    string Name;
    std::weak_ptr<pid_t> WkTid;
    
    ThreadData(Thread::threadFunc func, const string &name, 
        shared_ptr<pid_t> tid) :
        Func(func), Name(name), WkTid(tid) {
    }

    void threadRun() const {
        shared_ptr<pid_t> pid = WkTid.lock();
        if (!pid) {
            *pid = current_thread::tid();
            pid.reset();
        }
        current_thread::t_tidname = Name.c_str();
        ::prctl(PR_SET_NAME, current_thread::t_tidname);
        Func();
        //throw exception
        current_thread::t_tidname = "finished";
    }
};//ThreadData

static void* StartThread(void *t) {
    ThreadData *tdata = (ThreadData*)t;
    tdata->threadRun();
    delete tdata; //这里不要忘记了
}

}//detail

}//muduo_test

using namespace muduo_test;

AtomicInt32 Thread::threadNum_;

Thread::Thread(const threadFunc func, const string &name) 
    :  func_(func),
       name_(name),
       started_(false),
       joined_(false),
       pthreadId_(0),
       tid_(make_shared<pid_t>(0)) {
    int num = threadNum_.getAndIncrement();
    if (name_.empty()) {
        name_ = "Thread_";
        name_ += num;
    }
}

Thread::~Thread() {
    /*
    std::cout << __func__
        << "  tid: " << current_thread::tid()
        << "  started_:" << started_
        << endl;*/
    if (started_ && !joined_) {
        ::pthread_detach(pthreadId_);
        std::cout << __func__
             << "pthread_detach tid:  " << current_thread::tid()
             << std::endl;        
    }
}

void Thread::
start() { 
//如果直接开始就调用了pthread_create那么就无法获得其tid，并修改其线程名
    assert(!started_);
    detail::ThreadData *tdata = 
        new detail::ThreadData(func_, name_, tid_);
    if (pthread_create(&pthreadId_, NULL, detail::StartThread, (void*)tdata) != 0) {
        delete tdata;
    }

    started_ = true;
}

int Thread::
join() { //return pthread_join() 's error number
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthreadId_, NULL);
}

/**
int main() {
    std::cout << "true is : " << (0==0) << std::endl;
    std::cout << "is main thread : "
         << current_thread::isMainThread()
         << " tid : "
         << current_thread::tid()
         << std::endl;
    return 0;
}*/
