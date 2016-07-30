#ifndef _STRING_H__
#define _STRING_H__

#include <iostream>
#include <memory>
#include <utility>
#include <cstring>

using std::allocator;
using std::cout;
using std::endl;

class String {
public:

    String();

    String(const char *);
    
    String(const String &);

    String & operator=(const String &);

    ~String();

    char *begin() const { return elements; }
    const char *cbegin() const { return (const char*)elements; }

    size_t size() const {
        if (elements) return strlen(elements); 
        else return 0;
    }

private:

    void destroy();

    char *reallocator(const char *);

    std::pair<char*, char*>
        alloc_n_copy(const char*, const char*);   

    char *elements;
    //char *free;

    static allocator<char> alloc;
};

#endif
