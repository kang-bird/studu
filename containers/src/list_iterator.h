#ifndef SRC_LIST_ITERATOR_H_
#define SRC_LIST_ITERATOR_H_

#include "containers.h"

namespace study {

template <typename T, typename Node>
class list_iterator {
 public:
    Node *ptr;
    Node *root;
    Node *tail;

 public:
    using value_type = T;
    using reference = value_type&;
    using iterator = list_iterator<T, Node>;
    using size_type = size_t;

 public:
    list_iterator() : ptr(nullptr), root(nullptr), tail(nullptr) {}
    list_iterator(Node* new_ptr, Node* new_root, Node* new_tail)
                    : ptr(new_ptr), root(new_root), tail(new_tail) {}
    iterator& operator= (const iterator& other) {
        root = other.root;
        tail = other.tail;
        ptr = other.ptr;
        return (*this);
    }
    reference operator*() const {
        if (this->ptr == nullptr)
            throw std::out_of_range("Error: Incorrect iterator");
        return this->ptr->data;
    }

    iterator& operator++ () {
        if (this->root == this->tail)
            throw std::out_of_range("Error: List is empty");
        if (this->ptr->next == nullptr) {
            while (root->prev != nullptr)
                root = root->prev;
            this->ptr = root->next;
        } else {
            this->ptr = this->ptr->next;
        }
        return *this;
    }

    iterator& operator-- () {
        if (this->root == this->tail)
            throw std::out_of_range("Error: List is empty");
        if (this->ptr->prev->prev == nullptr) {
            while (tail->next != nullptr)
                tail = tail->next;
            this->ptr = tail;
        } else {
            this->ptr = this->ptr->prev;
        }
        return *this;
    }

    bool operator==(const iterator& other) {
        return (ptr->data == other.ptr->data);
    }

    bool operator!=(const iterator& other) {
        return (ptr->data != other.ptr->data);
    }
};

template <typename T, typename Node>
class const_list_iterator : public study::list_iterator<T, Node> {
 public:
    using value_type = T;
    using reference = const value_type&;
    using const_reference = const T&;
    using const_iterator = const_list_iterator<T, Node>;
    using iterator = study::list_iterator<T, Node>;
    using size_type = size_t;

 public:
    const_list_iterator() : study::list_iterator<T, Node>()  {}
    const_list_iterator(Node* new_ptr, Node* new_root, Node* new_tail)
                        : study::list_iterator<T, Node>(new_ptr, new_root, new_tail) {}
    Node* operator->() { return this->ptr; }
    Node* operator->() const { return this->ptr; }
    explicit const_list_iterator(const iterator& other) : const_list_iterator() {
            this->root = other.root;
            this->tail = other.tail;
            this->ptr = other.ptr;
    }

    const_reference operator*() const {
        if (this->ptr == nullptr)
            throw std::out_of_range("Error: Incorrect iterator");
        return this->ptr->data;
    }

    const_iterator& operator= (iterator other) {
        this->root = other.root;
        this->tail = other.tail;
        this->ptr = other.ptr;
        return (*this);
    }
};
}  // namespace study

#endif  // SRC_LIST_ITERATOR_H_
