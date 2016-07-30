#include <iostream>
#include <utility>

//complier by c++11: g++ -std=c++11
//本代码为了说明右值引用 & 左值引用
//右值引用 只有C++11才有的新特性
//右值引用 只能绑定到一个将要销毁的对象
//         不能直接绑定到左值对象上
//
using namespace std;

int main() {
    int i = 42;
    int &r = i;
    //int &&rr = i;//ERROR i:lvalue 

    //int &r2 = 2*i;//ERROR 2*i:rvalue
    const int &c_r3 = 2*i; //我们可以将一个const的引用绑定到一个右值上
    int &&rr2 = 2*i;

    //int &&rr3 = rr2; //ERROR: 变量表达式都是左值
    int &&rr3 = std::move(rr2);//使用move来获得绑定到左值上的右值引用
    //move调用告诉编译器：我们有一个左值，但我们希望像一个右值一样处理它
    //我们必须认识到调用了move之后，除了对rr2赋值或销毁它外，我们将不再使用它
    return 0;
}
