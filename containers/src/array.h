#ifndef SRC_ARRAY_H_
#define SRC_ARRAY_H_

#include "containers.h"

namespace study {
template <class T, std::size_t N>
class array : public sequence_container<T> {
 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

 public:
    /* --------------ARRAY FUNCTIONS-------------- */
    array():sequence_container<T>(N) {}
    explicit array(std::initializer_list<value_type> const &items): sequence_container<T>(N) {
        if (N < items.size())
            throw(std::length_error("Excess elements in array initializer"));
        size_t index = 0;
        for (T item : items) this->_arr[index++] = item;
    }
    array(const array&v);
    array(array &&v);
    ~array() {}
    array& operator=(const array &v);
    array& operator=(array &&v);

    /* --------------ARRAY CAPACITY-------------- */
    size_type max_size() const noexcept { return N; }

    /* --------------ARRAY MODIFIERS-------------- */
    void swap(array& other) noexcept;
    void fill(const_reference value);
};
}  // namespace study

#endif  // SRC_ARRAY_H_
