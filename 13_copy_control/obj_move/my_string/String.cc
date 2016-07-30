#include <iostream>
#include <memory>
#include <utility>
#include <cstring>
#include "String.h"

using namespace std;

allocator<char> String::alloc;

pair<char*, char*>
String::alloc_n_copy(const char *b, const char *e) {
    char *data = alloc.allocate(e - b);
    return make_pair(data, 
        uninitialized_copy(b, e, data));
}

char *
String::reallocator(const char *cstr) {
    char *e = const_cast<char*>(cstr);
    while(*e) ++e;
    pair<char*, char*> newdata = 
        alloc_n_copy(cstr, ++e); 
    //这里必须++e,因为alloc_n_copy的e必须为指定范围的最后一个指针
    return newdata.first;
}

void
String::destroy() {
    const size_t sz = size();
    if (sz) {
        alloc.destroy(elements);
        alloc.deallocate(elements, sz);
    }
}

String::String() {
    const char *e = "0"; //important
    elements = reallocator(e);
    cout << "constructor default" << endl;
}

String::String(const char *cstr) {
    elements = reallocator(cstr); 
    cout << "constructor char* : " 
         << elements << endl;
}

String::String(const String &str) {
    elements = reallocator(str.cbegin());    
    cout << "constructor copy : " 
         << elements << endl;
}

String &
String::operator=(const String &str) {//use const String str can ok
    char *newdata = reallocator(str.cbegin()); 
    //必须先复制，不然如果是自己对自己使用operator=就会引发段错误
    destroy();
    elements = newdata;
    cout << "operator =: "
         << elements << endl;
    return *this;
}

String::~String() {
    cout << "destructor : "
         << elements << endl;
    destroy();
}
