#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <string>
#include <memory>

using std::string;
using std::allocator;

class StrVec {
public:
    StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    ~StrVec();

    void push_back(const string &);

private:
    static allocator<string> alloc;
    string *element;
    string *first_free;
    string *cap;             // end
};

/*
 * usage:
 * like vector<string>
 *
 * push_back
 * pop
 * and so on...
 */

#endif
