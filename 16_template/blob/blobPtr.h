#ifndef _BLOB_PTR_H_
#define _BLOB_PTR_H_

#include <vector>
#include <memory>

template <typename T> class Blob;

template <typename T> class BlobPtr {
public:
    BlobPtr() : curr(0) { }
    BlobPtr(Blob<T> &a, size_t sz = 0) :
        wptr(a.data) ,curr(sz) { }

    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    //这里因为是在类模板自己的作用域内，
    //我们可以直接使用模板名而不提供实参
    //所以这里可以不写T
    BlobPtr& operator++(); //前置运算符
    BlobPtr& operator--();

private:
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string &) const;

    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

#endif
