#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_
#include "containers.h"

namespace study {
template <class T>
class vector : public sequence_container<T> {
 private:
    size_t _capacity;

 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

 public:
    /* --------------VECTOR FUNCTIONS-------------- */
    vector():sequence_container<T>() {_capacity = 0;}
    explicit vector(size_type n) : sequence_container<T>(n) {_capacity = n;}
    explicit vector(std::initializer_list<value_type> const &items);
    vector(const vector &v);
    vector(vector &&v);
    ~vector() {_capacity = 0;}
    vector& operator=(vector &&v);

    /* --------------VECTOR CAPACITY-------------- */
    void reserve(size_type n);
    size_type capacity() const noexcept { return _capacity; }
    void shrink_to_fit();
    size_type max_size() const noexcept {
        return (std::numeric_limits<size_type>::max() / (2 * sizeof(value_type)));
    }

    /* --------------VECTOR MODIFIERS-------------- */
    void clear() noexcept;
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const T& value);
    void pop_back();
    void swap(vector& other) noexcept;
    void resize(size_t n, const T& value = T());

    /* --------------VECTOR BONUS-------------- */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args &&...args);
    template <typename... Args>
    void emplace_back(Args &&...args);
};
}  // namespace study

#endif  // SRC_VECTOR_H_
