#ifndef _MUDUO_TEST_MUTEX_H_
#define _MUDUO_TEST_MUTEX_H_

#include <pthread.h>
#include "../thread/currentThread.h"
#include <assert.h>

#define assert_zero(cond) assert((cond) == 0)

namespace muduo_test {

class MutexLock {
public:
    explicit MutexLock() : holder_(0){
        assert_zero(pthread_mutex_init(&mutex_, NULL));
    }

    ~MutexLock() {
        assert(holder_ == 0);
        pthread_mutex_destroy(&mutex_);
    }

    bool isLockedByThisThread() const {
        return holder_ == current_thread::tid();
    }

    void assertLocked() const {
        assert(isLockedByThisThread());
    }

    void lock() {
        assert_zero(pthread_mutex_lock(&mutex_));
        assignHolder();
    }

    void unlock() {
        assert_zero(pthread_mutex_unlock(&mutex_));
        unassignHolder();
    }

    bool trylock() {
        bool lock = (pthread_mutex_trylock(&mutex_) == 0);
        if (lock)
            assignHolder();
        return lock;
    }

    pthread_mutex_t &getMutex() {
        return mutex_;
    }
private:
    class UnassignGuard {
    public:
        UnassignGuard() {
            unassignHolder();
        }

        ~UnassignGuard() {
            assignHolder();
        }
    };


    void unassignHolder() {
        holder_ = 0;
    }

    void assignHolder() {
        holder_ = current_thread::tid();
    }

    pthread_mutex_t mutex_;
    pid_t holder_;
};//Mutex

class MutexLockGuard { // RAII
public:
    explicit MutexLockGuard(MutexLock &mutex) :
        mutex_(mutex) { 
        mutex_.lock();
    }

    ~MutexLockGuard() {
        mutex_.unlock();
    }
private:
    MutexLock &mutex_;
};


}//muduo_test
#endif
