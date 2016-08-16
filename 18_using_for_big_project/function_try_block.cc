#include <iostream>
#include <stdexcept>

using namespace std;

//因为在初始值列表抛出异常时构造函数体内的
//try语句块还未生效，所以构造函数体内的catch语句
//无法处理构造函数初始值列表抛出的异常
//
//要想处理函数初始值抛出的异常，必须将构造函数写成
//函数try语句块（function try block）
//
//但经过使用，函数try语句块即使catch了也会向外继续抛出
//而普通的函数体的catch语句中如果不再次throw是不会再抛出

class Data {
public:
    Data(const int &id) try:
        id_(id) {
        if (id<0) throw logic_error("Data:id<0");
    }catch(const logic_error &ler) {
        cout <<__func__ << " catch logic_error:"
             << ler.what() << endl;
        //throw;
    }
private:
    unsigned int id_;
};

class Usage {
public:
    Usage(const int &id) try :
        data_(id) {
        cout << __func__ << endl;
    }catch(const exception &e) {
        cout << __func__ << " catch exception: "
             << e.what() << endl;
    }
private:
    Data data_;
};

int main() {
    try{
        //Data data(-1);
        Usage u(-1);
    }
    catch(const exception &e) {
        cout << __func__
             << " catch exception: " << e.what() << endl;
    }
    return 0;
}
