#ifndef __STR_VEC_H_
#define __STR_VEC_H_

#include <string>
#include <memory>
#include <utility>

using std::string;
using std::allocator;
using std::pair;
/*
 * usage : use like vector<string>
 * func: push_back;
 *       begin / end;
 */

class StrVec {
public:
    StrVec() : 
        elements(NULL), first_free(NULL), cap(NULL) {}

    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    ~StrVec() { free(); }

    void push_back(const string &);
    
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    string *begin() const { return elements; }
    string *end()   const { return first_free; } 
private:
    pair<string*, string*> alloc_n_copy
        (string *, string *);
    void chk_n_allocate() 
        { if (size() == capacity()) reallocate(); }
    void reallocate(); //扩展内存
    void free();
    string *elements;
    string *first_free;
    string *cap;
    static allocator<string> alloc;
};

#endif
