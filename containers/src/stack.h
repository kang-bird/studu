#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include "containers.h"

namespace study {
template <class T>
class stack {
 private:
    struct Node {
        T data;
        Node *next;
        Node() {}
        explicit Node(const T& val, Node* n = nullptr) : data(val), next(n) {}
    };
    Node* _root;
    size_t _size;

 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 public:
    /* --------------STACK MEMBER FUNCTIONS-------------- */
    stack() : _root(nullptr), _size(0U) {}
    explicit stack(std::initializer_list<value_type> const &items);
    stack(const stack &s);
    stack(stack &&s);
    ~stack() {
        while (!empty()) {
            pop();
        }
        _size = 0;
    }
    stack& operator=(stack &&s);

    /* --------------STACK ELEMENT ACCESS-------------- */
    const_reference top() const;

    /* --------------STACK CAPACITY-------------- */
    bool empty() const { return _root == nullptr; }
    size_type size() const {return _size;}

    /* --------------STACK MODIFIERS-------------- */
    void pop();
    void push(const_reference value);
    void swap(stack& other) noexcept;

    /* --------------STACK BONUS-------------- */
    template <typename... Args>
    void emplace_front(Args&&... args);
};
}  // namespace study

#endif  // SRC_STACK_H_
