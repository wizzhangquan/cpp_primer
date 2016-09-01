#ifndef _MUDUO_TEST_THREAD_CURRENT_THREAD_H_
#define _MUDUO_TEST_THREAD_CURRENT_THREAD_H_

//#define _GNU_SOURCE
#include <string>
#include <stdint.h>
#include <time.h>

namespace muduo_test {

namespace detail {
    int gettid();
}//detail

namespace current_thread {
//__thread全局变量丢入此namespace

extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char *t_tidname;

inline int tid(void) {
    if (__builtin_expect(t_cachedTid == 0, 0)) {
        t_cachedTid = detail::gettid();
    }
    return t_cachedTid;
}

inline const char *tidString() {
    return t_tidString;
}

inline const char *name() {
    return t_tidname;
}

bool isMainThread();

}//current_thread

}//muduo_test

#endif
