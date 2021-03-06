#include <vector>
#include <memory>
#include <stdexcept>
#include "blobPtr.h"

using namespace std;

template <typename T>
shared_ptr<vector<T>> BlobPtr<T>::
check(size_t i, const string &msg) const {
    auto retVect = wptr.lock();
    if (!retVect)
        throw runtime_error("unbound BlobPtr");
    if (i >= retVect.size() || i < 0)
        throw out_of_range(msg);
    return retVect;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    auto p = check(curr+1, "out of range vector"); 
    ++curr;
    return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    auto p = check(curr-1, "less range");
    --curr;
    return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int) {
    BlobPtr ret = *this;
    //这里是在类模板作用域内，
    //所以可以直接使用模板名不需要加上T
    ++*this;
    return ret;
}

int main() {
    return 0;
}
