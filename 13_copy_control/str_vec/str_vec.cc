#include <iostream>
#include "str_vec.h"

using namespace std;

allocator<string> StrVec::alloc; //这里必须要给静态变量一个定义！！
                                 //在头文件处，只是声明，并没有定义，并且只定义一次
                                 //静态变量只能初始化一次，只能在类定义外面初始化

void
StrVec::reallocate() {
    size_t new_size = size() > 0 ? 2*size() : 1;
    auto newdata = alloc.allocate(new_size);
}

int main() {
    return 0;
}
