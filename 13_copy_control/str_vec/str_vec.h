#ifndef __STR_VEC_H_
#define __STR_VEC_H_

#include <string>
#include <memory>

using std::string;
using std::allocator;
/*
 * usage : use like vector<string>
 * func: push_back;
 *       begin / end;
 */

class StrVec {
public:
    StrVec() : 
        elements(NULL), first_free(NULL), cap(NULL) {}
    
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
 
private:
    void reallocate(); //扩展内存
    string *elements;
    string *first_free;
    string *cap;
    static allocator<string> alloc;
};

#endif
