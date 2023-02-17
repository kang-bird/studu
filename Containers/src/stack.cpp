#include "stack.h"

namespace study {

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
    _size = 0;
    _root = nullptr;
    auto x = items.begin();
    while (x < items.end()) {
        this->push(*x);
        x++;
    }
    this->_size = items.size();
}

template <class T>
stack<T>::stack(const stack &s) {
    if (s.empty()) {
        _root = nullptr;
    } else {
        Node* position = s._root;
        Node* tmp = new Node(position->data);
        _root = tmp;
        Node* tail = tmp;
        while (position->next != nullptr) {
            position = position->next;
            tmp = new Node(position->data);
            tail->next = tmp;
            tail = tmp;
        }
    }
    _size = s._size;
}

template <class T>
stack<T>::stack(stack &&s) {
    _root = nullptr;
    operator=(std::move(s));
}

template <class T>
typename stack<T>::const_reference stack<T>::top() const {
    if (empty()) {
        throw std::length_error("stack is empty");
    }
    return _root->data;
}

template <class T>
void stack<T>::pop() {
    if (empty()) {
        throw std::length_error("stack is empty");
    }
    Node * delnode = _root;
    _root = delnode->next;
    delete delnode;
    if (_size > 0)
        _size--;
}

template <class T>
void stack<T>::push(const_reference value) {
    Node* newnode = new Node;
    newnode->data = value;
    newnode->next = _root;
    _root = newnode;
    _size++;
}

template <class T>
void stack<T>::swap(stack& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_root, other._root);
}

template <class T>
stack<T>& stack<T>::operator=(stack<T> &&other) {
    if (&other == this)
        return *this;
    this->~stack();
    this->_root = std::exchange(other._root, nullptr);
    this->_size = std::exchange(other._size, 0);
    return *this;
}

template <class T>
template <typename... Args>
void stack<T>::emplace_front(Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    while (x < input_vector.end()) {
        push(*x);
        x += 1;
    }
}
}  // namespace study
