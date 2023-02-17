#ifndef SRC_CONTAINERS_H_
#define SRC_CONTAINERS_H_
#include <iostream>
#include <limits>
#include <utility>
#include <memory>
#include <vector>

namespace study {
template <class T>
class sequence_container {
 protected:
    T* _arr;
    size_t _size;

 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

 public:
    /* --------------CONTAINER FUNCTIONS-------------- */
    sequence_container(): _arr(nullptr), _size(0U) {}
    explicit sequence_container(size_type n) : _arr(n ? new value_type[n]() : nullptr), _size(n) {}
    ~sequence_container() { delete[] _arr,  _size = 0;}

    /* --------------CONTAINER ELEMENT ACCESS-------------- */
    reference at(size_t i) {return this->_arr[i];}
    reference operator[] (size_t i) {return _arr[i];}
    const_reference operator[] (size_t i) const {return _arr[i];}
    const_reference front() const {return const_reference(this->_arr[0]);}
    const_reference back() const {return const_reference(this->_arr[this->_size-1]);}
    iterator data() noexcept {return iterator(_arr);};

    /* --------------CONTAINER ITERATORS-------------- */
    iterator begin() noexcept {return iterator(this->_arr);}
    iterator end() noexcept {return iterator(&this->_arr[this->_size]);}
    const_iterator cbegin() noexcept {return iterator(this->_arr);}
    const_iterator cend() noexcept {return iterator(&this->_arr[this->_size]);}

    /* --------------CONTAINER CAPACITY-------------- */
    bool empty() const noexcept {return (!_size);}
    size_type size() const noexcept {return _size;}
};
}  // namespace study

#endif  // SRC_CONTAINERS_H_

