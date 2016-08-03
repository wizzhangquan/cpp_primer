#include <iostream>

/*
 * 如下：
 * 在声明了情况下，
 * 并不需要include头文件
 * 这样可以保护避免头文件相互包含
 */

class s;
static void static_func();
void test_local_static_var();

using namespace std;

int main() {
    cout << __func__ << endl;
    test_local_static_var();
    return 0;
}
