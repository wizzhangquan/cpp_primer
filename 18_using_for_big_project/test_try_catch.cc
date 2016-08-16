#include <iostream>
#include <stdexcept>

using namespace std;

void foo(void) {
    cout << __func__ << "begin" << endl;
    throw out_of_range("foo out_of_range");
    cout << __func__ << "end" << endl;
}

void bar(void) {
    try{
        foo();
    }catch(...) {
        cout << __func__ << " catch ..."
             << endl;
        throw;
    }
}


int main() {
    try{
        bar();
    }catch(const out_of_range &oor) {
        cout << "out_of_range error: "
             << oor.what() << endl;
        //throw ; //ERROR
        //这里的catch都是平级的，
        //只能捕获前面try抛出的异常
        //而在里面throw的话
        //只能被该区域外层的try catch捕获
        //也就是说，
        //main函数中不能再catch中使用throw了
        //如果没有双层try那将不会被捕获到
        //同时出现段错误
    }catch(const exception &ep) {
        cout << "exception error: "
             << ep.what() << endl;
    }
    catch(...) {
        cout << "catch ..." << endl;
    }
    return 0;
}
