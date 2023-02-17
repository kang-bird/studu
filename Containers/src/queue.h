#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include "containers.h"

namespace study {
template <class T>
class queue {
 private:
    struct Node {
        T data;
        Node *next;
        Node() {}
        explicit Node(const T& val, Node* n = nullptr) : data(val), next(n) {}
    };
    Node* _root;
    Node* _tail;
    size_t _size;

 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 public:
    /* --------------QUEUE MEMBER FUNCTIONS-------------- */
    queue() : _root(nullptr), _tail(nullptr), _size(0U) {}
    ~queue() {
        while (!empty()) {
            pop();
        }
        _size = 0;
    }
    explicit queue(std::initializer_list<value_type> const &items);
    queue(const queue &q);
    queue(queue &&q);
    queue& operator=(queue &&q);

    /* --------------QUEUE ELEMENT ACCESS-------------- */
    const_reference front() const { return _root -> data; }
    const_reference back() const { return _tail -> data; }

    /* --------------QUEUE CAPACITY-------------- */
    bool empty() const { return _root == nullptr; }
    size_type size() const {return _size;}

    /* --------------QUEUE MODIFIERS-------------- */
    void push(const_reference value);
    void pop();
    void swap(queue& other) noexcept;

    /* --------------STACK BONUS-------------- */
    template <typename... Args>
    void emplace_back(Args&&... args);
};
}  // namespace study

#endif  // SRC_QUEUE_H_
