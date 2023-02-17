#include "vector.h"
#include <cstring>

namespace study {

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
    this->_arr = new value_type[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
        this->_arr[i] = *it;
        i++;
    }
    this->_size = items.size();
    _capacity = items.size();
}

template <class T>
vector<T>::vector(const vector &v) {
    this->_size = v.size();
    _capacity = v.capacity();
    this->_arr = new value_type[this->_capacity]();
    for (size_type i = 0; i < this->_size; ++i)
        this->_arr[i] = v._arr[i];
}


template <class T>
vector<T>::vector(vector &&v) {
    this->_size = v._size;
    _capacity = v._capacity;
    this->_arr = v._arr;
    v._arr = nullptr;
    v._size = 0;
    v._capacity = 0;
}


template <class T>
void vector<T>::reserve(size_t size) {
    if (size > this->max_size())
                        throw(std::length_error("Not enough space"));
    if (size <= _capacity) return;
    T* newarr = new value_type[size]();
    for (size_t i = 0; i < this->_size; i++) {
        new (newarr + i) T(this->_arr[i]);
    }
    if (this->_arr) {
        delete[] this->_arr;
        this->_arr = nullptr;
    }
    this->_arr = newarr;
    _capacity = size;
}

template <class T>
void vector<T>::resize(size_t n, const T& value) {
    while (n < this->_size)
        pop_back();
    if (n > this->_capacity)
            reserve(n);
    while (n > this->_size)
            push_back(value);
}

template <class T>
void vector<T>::push_back(const T& value) {
    if (_capacity == this->_size) {
        if (this->_size == 0)
            reserve(1);
        else
            reserve(2 * this->_size);
    }
    new(&this->_arr[this->_size++]) T(value);
}

template <class T>
void vector<T>::pop_back() {
    --this->_size;
    (this->_arr+this->_size)->~T();
}

template <class T>
void vector<T>::clear() noexcept {
    while (this->_size)
        pop_back();
}

template <class T>
void vector<T>::swap(vector& other) noexcept {
    std::swap(this->_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(this->_arr, other._arr);
}

template <class T>
vector<T>& vector<T>::operator=(vector<T> &&v) {
        if (this == &v)
            return *this;
        delete[] this->_arr;
        this->_arr = std::exchange(v._arr, nullptr);
        this->_size = std::exchange(v._size, 0);
        _capacity = std::exchange(v._capacity, 0);
        return *this;
}

template <class T>
void vector<T>::erase(const iterator pos) {
    for (size_type i = pos - this->begin() ; i < this->_size - 1 ; ++i) {
        this->_arr[i] = this->_arr[i + 1];
    }
    pop_back();
}

template <class T>
typename vector<T>::iterator vector<T>::insert(const iterator pos, const_reference value) {
    size_type i = pos - this->begin();
    if (_capacity < this->_size + 1)
        this->reserve(this->_size + 1);
    size_type j = _capacity - 1;
    while (j > i) {
        this->_arr[j] = this->_arr[j - 1];
        j = j - 1;
    }
    this->_arr[i] = value;
    this->_size++;
    return (iterator(&this->_arr[i]));
}

template <class T>
void vector<T>::shrink_to_fit() {
    if (_capacity > this->_size) {
        T* newarr = new value_type[this->_size]();
        for (size_t i = 0; i < this->_size; i++) {
            new (newarr + i) T(this->_arr[i]);
        }
        if (this->_arr) {
            delete[] this->_arr;
            this->_arr = NULL;
        }
        this->_arr = newarr;
        _capacity = this->_size;
    }
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos, Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    do {
    size_type i = pos - this->begin();
    if (_capacity < this->_size + 1)
        this->reserve(this->_size + 1);
    size_type j = _capacity - 1;
    while (j > i) {
        this->_arr[j] = this->_arr[j - 1];
        j = j - 1;
    }
    this->_arr[i] = *x;
    this->_size++;
    } while (x < input_vector.end()-1);
    return iterator(pos);
}


template <class T>
template <typename... Args>
void vector<T>::emplace_back(Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    while (x < input_vector.end()) {
        push_back(*x);
        x += 1;
    }
}
}  // namespace study