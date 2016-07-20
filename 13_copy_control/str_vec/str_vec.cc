#include <memory>
#include <iostream>
#include <string>
#include "str_vec.h"

using namespace std;

void
StrVec::push_back(const string &str) {
    chk_n_alloc();
    alloc.construct(first_free++, str); 
}

void
StrVec::free(void) {
    if (element) {
        for (string *p = first_free; p != element; ) //这里为何是逆序
            alloc.destroy(--p);
        alloc.deallocate(element, cap - element);
    }
}

void 
StrVec::reallocate(void) {
    size_t orign_size = size();
    size_t new_size = orign_size > 0 ? 2*orign_size : 1;

    string *newdata = alloc.allocate(new_size);
    string *dest = newdata;

    for (string *i = element; i < first_free; ++i)
        alloc.construct(dest++, *i);

    free();

    element = newdata;
    first_free = dest;
    cap = newdata + new_size;
}

int main(void) {
    StrVec sv;
    
    sv.push_back("hello");
    sv.push_back("world");
    sv.push_back("msy");
    sv.push_back("zach");
    
    for (string* s = sv.begin(); s != sv.end(); ++s)
        cout << s << endl;    
    return 0;
}
