#include <iostream>
#include "atomic.h"

using namespace muduo_test;
using std::cout;
using std::endl;

int main() {
    detail::Atomic<int> a(6);
    cout << a.get() << endl;
    cout << a.incrementAndGet() << endl;
    return 0;
}
