#include <iostream>
#include <utility>
#include <memory>
#include <string>
#include "str_vec.h"

using namespace std;

allocator<string> StrVec::alloc; //这里必须要给静态变量一个定义！！
                                 //在头文件处，只是声明，并没有定义，并且只定义一次
                                 //静态变量只能初始化一次，只能在类定义外面初始化

StrVec::StrVec(const StrVec &rhs) {
    pair<string *, string *> data = 
        alloc_n_copy(rhs.begin(), rhs.end());
    elements = data.first;
    cap = first_free = data.second;
}

StrVec &
StrVec::operator=(const StrVec &rhs) {
    pair<string *, string *> data = 
        alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    cap = first_free = data.second;
    return *this;
}

void
StrVec::push_back(const string &str) {
    chk_n_allocate();
    alloc.construct(first_free++, str);
    //cout << "push_back sz:"<< size() << " cap" << capacity() << endl; 
}

pair<string*, string*>
StrVec::alloc_n_copy(string *begin, string *end) {
    string *data = alloc.allocate(end - begin);
    return pair<string*, string*> (
            data, uninitialized_copy(begin, end, data) );
}

void
StrVec::free() {
    if (elements) {
        for (string *s = first_free; s != elements; )
            alloc.destroy(--s);
        alloc.deallocate(elements, cap-elements);
    }
}

void
StrVec::reallocate() {
    size_t newsize = size() > 0 ? 2*size() : 2;
    string *newdata = alloc.allocate(newsize);

    string *dest = newdata;
    for (string *elem = elements; elem != first_free; ++elem)
        alloc.construct(dest++, *elem);

    free();

    elements = newdata;
    first_free = dest;
    cap = newdata + newsize;
}

int main() {
    string str;
    StrVec sv;
    while (cin >> str) {
        if (str == "q") break;
        sv.push_back(str);
    }
    cout << "print sv: ";
    for (string *s = sv.begin(); s != sv.end(); ++s)
        cout << *s << " ";
    cout << endl;
 
    return 0;
}
