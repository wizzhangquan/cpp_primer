#include <iostream>

using namespace std;

void test_ref_incre(int &a) {
    cout << __func__ 
         <<  " left ref: " << a << endl;
}

void test_ref_incre(int &&a) {
    cout << __func__
         << " right ref: " << a << endl;
}

int main() {
    int a = 1;
    cout << "test ++a" << endl;
    test_ref_incre(++a);
    
    cout << endl;
    int b = 1;
    cout << "test b++" << endl;
    //b++返回的是一个右值，那么如果要使用左值引用一个右值
    //必须是 const Type & 因为左值const &可以引用右值
    //或者 使用 Type &&来一个函数重载
    test_ref_incre(b++);
    return 0;
}
