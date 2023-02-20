#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include "list_iterator.h"

namespace study {
template <class T>
class list {
 private:
    struct Node {
        T data;
        Node *prev;
        Node *next;
        Node() : prev(nullptr), next(nullptr), data() {}
        explicit Node(const T &val, Node* new_prev = nullptr, Node* new_next = nullptr) {
            this->data = val;
            this->next = new_next;
            this->prev = new_prev;
        }
        Node& operator =(const Node& other) {
            if (this != &other) {
                this->data = other.data;
                this->prev = other.prev;
                this->next = other.next;
            }
            return (*this);
        }
    };
    Node* _root;
    Node* _tail;
    size_t _size;

 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = list_iterator<T, Node>;
    using const_iterator = const_list_iterator<T, Node>;
    using size_type = size_t;

 public:
    /* --------------LIST FUNCTIONS-------------- */
    list();
    explicit list(size_type n);
    explicit list(std::initializer_list<value_type> const &items);
    list(const list &l);
    list(list &&l);
    ~list();
    list& operator=(list &&other) noexcept;

    /* --------------LIST ELEMENT ACCESS-------------- */
    const_reference front() const {return _root -> next -> data;}
    const_reference back() const {return _tail -> prev -> data;}

    /* --------------LIST ITERATORS-------------- */
    iterator begin() {return iterator(_root->next, _root, _tail);}
    iterator end() noexcept {return iterator(_tail, _root, _tail);}
    const_iterator cbegin() const noexcept {return const_iterator(_root->next, _root, _tail);}
    const_iterator cend() const noexcept {return const_iterator(_tail, _root, _tail);}

    /* --------------LIST CAPACITY-------------- */
    bool empty() const noexcept {return (_size == 0);}
    size_type size() const noexcept {return _size;}
    size_type max_size() const noexcept {return (std::numeric_limits<size_type>::max() / (sizeof(Node)));}

    /* --------------LIST MODIFIERS-------------- */
    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();
    void swap(list& other) noexcept;
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse() noexcept;
    void unique();
    void sort();

    /* --------------LIST BONUS-------------- */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    template <typename... Args>
    void emplace_back(Args&&... args);
    template <typename... Args>
    void emplace_front(Args&&... args);
};
}  // namespace study

#endif  // SRC_LIST_H_
