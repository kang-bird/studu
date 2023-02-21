#include "array.h"

namespace study{

template <class T, std::size_t N>
array<T, N>::array(const array &v) {
    if (N < this->_size)
        throw(std::length_error("Excess elements in array initializer"));
    this->_size = v.size();
    this->_arr = new value_type[this->_size]();
    for (size_type i = 0; i < this->_size; ++i)
        this->_arr[i] = v._arr[i];
}

template <class T, std::size_t N>
array<T, N>::array(array &&v) : array(v) {}


template <class T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array<T, N> &v) {
    if (this->_size != v._size) {
        throw(std::out_of_range("Must have same size"));
    }
    if (this != &v) {
        std::copy(v._arr, v._arr + v._size, this->_arr);
    }
    return *this;
}

template <class T, std::size_t N>
array<T, N>& array<T, N>::operator=(array<T, N> &&v) {
    if (this == &v)
        return *this;
    operator=(v);
    return *this;
}

template <class T, std::size_t N>
void array<T, N>::swap(array& other) noexcept {
    std::swap(this->_arr, other._arr);
}

template <class T, std::size_t N>
void array<T, N>::fill(const_reference value) {
    for (iterator i = this->begin(); i != this->end(); ++i)
        *i = value;
}
}  // namespace study
