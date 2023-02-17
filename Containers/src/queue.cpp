#include "queue.h"

namespace study {

template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items) {
    _root = nullptr;
    _size = 0;
    auto x = items.begin();
    while (x < items.end()) {
        this->push(*x);
        x++;
    }
    this->_size = items.size();
}

template <class T>
queue<T>::queue(const queue &q) {
    if (q.empty()) {
        _root = nullptr;
        _tail = nullptr;
    } else {
        Node* position = q._root;
        Node* tmp = new Node(position->data);
        _root = tmp;
        _tail = tmp;
        while (position->next != nullptr) {
            position = position->next;
            tmp = new Node(position->data);
            _tail->next = tmp;
            _tail = tmp;
        }
    }
    _size = q._size;
}

template <class T>
queue<T>::queue(queue &&s) {
    _root = nullptr;
    operator=(std::move(s));
}

template <class T>
queue<T>& queue<T>::operator=(queue<T> &&other) {
    if (&other == this)
        return *this;
    this->~queue();
    this->_root = std::exchange(other._root, nullptr);
    this->_tail = std::exchange(other._tail, nullptr);
    this->_size = std::exchange(other._size, 0);
    return *this;
}


template <class T>
void queue<T>::push(const_reference value) {
    if (empty()) {
        _root = new Node(value);
        _tail = _root;
    } else {
        Node *tmp = new Node(value);
        _tail->next = tmp;
        _tail = _tail->next;
    }
    _size++;
}

template <class T>
void queue<T>::pop() {
    if (empty()) {
        throw std::length_error("stack is empty");
    }
    Node *temp = _root;
    _root = _root->next;
    delete temp;
    _size--;
}

template <class T>
void queue<T>::swap(queue& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_root, other._root);
    std::swap(_tail, other._tail);
}


template <class T>
template <typename... Args>
void queue<T>::emplace_back(Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    while (x < input_vector.end()) {
        push(*x);
        x += 1;
    }
}
}  // namespace study