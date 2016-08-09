#include <iostream>
#include <cstring>

using namespace std;

template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
    cout << "N:" << N
         << " M:" << M << endl;
    return strcmp(p1, p2);
}

int main() {

    //字符数组会自动在后面补一个'\0'
    //编译器会使用字面常量的大小来代替N和M，
    //从而实例化模板
    cout << compare("hello", "hello1") << endl;
    return 0;
}
