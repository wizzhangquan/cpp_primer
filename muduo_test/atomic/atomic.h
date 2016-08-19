#ifndef __MUDUO_TEST_ATOMIC_H_
#define __MUDUO_TEST_ATOMIC_H_

namespace muduo_test {

namespace detail {

template <typename Type> class Atomic {
public:
    Atomic() : numeric_(0) { }
    Atomic(const Type &n) : numeric_(n) { }

    Type get() {
        return __sync_val_compare_and_swap(&numeric_, 0, 0);
    }
    
    Type getAndAdd(const Type &a) {
        return __sync_fetch_and_add(&numeric_, a);
    }
    
    Type addAndGet(const Type &a) {
        return getAndAdd(a) + a; 
    }

    Type getAndIncrement() {
        return getAndAdd(1);
    }

    Type incrementAndGet() {
        return addAndGet(1);
    }

    Type getAndDecrement() {
        return getAndAdd(-1);
    }

    Type decrementAndGet() {
        return addAndGet(-1);
    }

    void increment() {
        getAndAdd(1);
    }

    void decrement() {
        getAndAdd(-1);
    }

    Type getAndSet(const Type &a) {
        return __sync_lock_test_and_set(&numeric_, a);
    }
    
    void set(const Type &a) {
        getAndSet(a);
    }
private:
    volatile Type numeric_; 
};
}

}

#endif
