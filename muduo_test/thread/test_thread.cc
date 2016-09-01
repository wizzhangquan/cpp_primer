#include "currentThread.h"
#include "thread.h"
#include <iostream>
#include <functional>
#include <stdio.h>
#include <unistd.h>

using namespace muduo_test;
using std::cout;
using std::endl;
using std::string;

//compile : g11 currentThread.h thread.h thread.cc test_thread.cc -lpthread

void functest1(void) {
    
    //cout << "hello "
    //     << __func__ << endl;
    char buf[100] = {0};
    snprintf(buf, 100, "%s: pid=%d, tid=%d\n",
             __func__, ::getpid(), muduo_test::current_thread::tid());
    sleep(1);
    write(STDOUT_FILENO, buf, sizeof(buf));
    //printf("%s: pid=%d, tid=%d\n",
    //        __func__, ::getpid(), muduo_test::current_thread::tid());

    //cout << "end "
    //     << __func__ << endl; 
}

static void functest2(int x) {
    printf("%s: pid=%d, tid=%d, x=%d\n",
            __func__, ::getpid(), 
            muduo_test::current_thread::tid(), x);
}

class Foo {
public:
    explicit Foo(const double x = 0) :
        x_(x) { }
    
    void memberFunc() {
        printf("%s: pid=%d, tid=%d, x=%f\n",
            __func__, ::getpid(), 
            muduo_test::current_thread::tid(), x_);
    }

    void memberFunc2(const std::string &tex) {
        printf("%s: pid=%d, tid=%d, tex=%s, x=%f\n",
            __func__, ::getpid(), 
            muduo_test::current_thread::tid(), 
            tex.c_str(), x_);
    }

private:
    double x_;
};

int main() {
    printf("hello main before thread start\n");
    printf("main: pid=%d, tid=%d\n", 
        ::getpid(), muduo_test::current_thread::tid());

    Thread t1(functest1);
    t1.start();
    t1.join();

    Thread t2(std::bind(functest2, 42));
    t2.start();
    t2.join();

    Foo foo(80.08);
    Thread t3(std::bind(&Foo::memberFunc, &foo)); //important
    t3.start();
    t3.join();

    Thread t4(std::bind(&Foo::memberFunc2, &foo, string("wizzhangquan")));
    t4.start();
    t4.join();

    {
        cout << endl << endl;
        Thread t5(functest1);
        t5.start();
        //::sleep(2); 
        //if not sleep ,will core dump. 
        //t5 destruct eariler than thread creation
    }

    printf("number of created threads %d\n", Thread::numCreated());
    return 0; 
}
