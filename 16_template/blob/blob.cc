#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include "blob.h"

using namespace std;

template <typename T>
void Blob<T>::check(size_type i, const string &msg) const {
    if (i >= data.size() || i < 0)
        throw std::out_of_range(msg);
}

template <typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) { }

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : 
    data(make_shared<vector<T>>(il)) { }

template <typename T>
void Blob<T>::pop_back() {
    check(0, "pop back on empty Blob");
    *data.pop_back();
}

template <typename T>
T& Blob<T>::back() {
    check(0, "back on empty Blob");
    return *data.back();
}

template <typename T>
T& Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return *data[i];
}

int main() {
    return 0;
}
