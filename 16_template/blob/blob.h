#ifndef _BLOB_H__
#define _BLOB_H__

#include <memory>
#include <vector>
#include <initializer_list>

template <typename T> class Blob {
public:
    typedef typename std::vector<T>::size_type size_type;

    Blob();
    Blob(std::initializer_list<T> il);

    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    
    void pop_back();
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T> > data;
    void check(size_type i, const std::string &msg) const;
};

#endif
