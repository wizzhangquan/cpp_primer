#include <iostream>

using namespace std;

//测试gcc内置的原子操作
//type __sync__fetch_and_add(type *ptr, type value)
//type __sync__fetch_and_sub
//type __sync__fetch_and_or
//type __sync__fetch_and_and
//
//type __sync_val_compare_and_swap(type *ptr, type oldval, type newval)
//type __sync_lock_test_and_set(type *ptr, type value)
//
//__sync_synchronize(); ===> 加上一个full barrier

int getAndIncrement(int *pVal) {
    return __sync_fetch_and_add(pVal, 1);
}

int main() {
    int v = 5;
    cout << "getAndIncrement:" << getAndIncrement(&v)
         << "   v:" << v
         << endl;
    cout << v << endl;
    return 0;
}
