#include <iostream>
#include <string>

using namespace std;

template <typename Type>
class NamedObj{
public:
    NamedObj(string &name, const Type& object) : 
        name_(name), object_(object) { }

    void printName(const string &preDesc) {
        cout << preDesc << name_ << " : " << &name_<< endl;
    }
private:
    string &name_; 
    /*
     * 当存在 引用的时候
     * 编译器在构造默认operator = 函数的时候是不知道如何复制引用的。
     * 毕竟：引用reference自身地址无法修改
     * 而修改引用所执行的对象时，这样会进而影响“持有pointer / reference
     * 而且指向该对像”的其他对象
     *
     * 所以不提供默认operator = 
     * 需要的话 自己定义
     */
    const Type object_;
};

int main() {
    string a, b;
    a = "hello";
    b = "world";
    NamedObj<int> n1(a, 1);
    NamedObj<int> n2(b, 2);

    n2 = n1;
    //n1.printName("n1 -> ");
    //n2.printName("n2 -> ");
    return 0;
}
