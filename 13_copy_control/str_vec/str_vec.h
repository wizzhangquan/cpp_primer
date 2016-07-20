#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <string>
#include <memory>
#include <utility>

using namespace std;
//using std::string;
//using std::pair;

class StrVec {
public:
    StrVec() : element(NULL), first_free(NULL), cap(NULL) {}
//    StrVec(const StrVec&);
//    StrVec &operator=(const StrVec&);
    ~StrVec() { free(); };

    void push_back(const string &);
    size_t size() const { return first_free - element; }
    size_t capacity() const { return cap - element; }
    string *begin() const { return element; }
    string *end() const { return first_free; };

private:
    static allocator<string>alloc;
    void chk_n_alloc() 
        { if (size() == capacity()) reallocate(); }
    pair<string* , string*>
        alloc_n_copy(const string *, const string *);
    void free();
    void reallocate();           //重分内存
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
