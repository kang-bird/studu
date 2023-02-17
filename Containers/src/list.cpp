#include "list.h"


/* ---------------------LIST FUNCTIONS--------------------- */
namespace study {

template <class T>
list<T>::list() : _root(nullptr), _tail(nullptr), _size(0U) {
    this->_root = new Node();
    this->_tail = new Node();
    this->_root->next = this->_tail;
    this->_tail->prev = this->_root;
}

template <class T>
list<T>::list(size_type n) : list() {
    _size = n;
    while (n-- > 0) {
        Node* new_node = new Node;
        new_node->next = this->_root->next;
        new_node->prev = this->_root;
        this->_root->next = new_node;
        this->_root->next->prev = new_node;
    }
}

template <class T>
list<T>::list(std::initializer_list<value_type> const &items) : list<T>::list() {
    auto x = items.begin();
    while (x < items.end()) {
        this->push_back(*x);
        x++;
    }
    this->_size = items.size();
}

template <class T>
list<T>::list(const list &l) : list<T>::list() {
    Node* position = l._root->next;
    while (position->next != nullptr) {
        push_back(position->data);
        position = position->next;
    }
    _size = l._size;
}

template <class T>
list<T>::list(list &&s) : list<T>::list() {
    operator=(std::move(s));
}

template <class T>
list<T>& list<T>::operator=(list<T> &&other) noexcept {
    if (&other == this)
        return *this;
    this->~list();
    this->_root = std::exchange(other._root, nullptr);
    this->_tail = std::exchange(other._tail, nullptr);
    this->_size = std::exchange(other._size, 0);
    return *this;
}

template <class T>
list<T>::~list() {
    this->clear();
    delete this->_tail;
    delete this->_root;
}

/* ---------------------LIST MODIFIERS--------------------- */

template <class T>
void list<T>::push_back(const value_type &value) {
    Node* ptr = new Node(value);
    ptr->next = _tail;
    ptr->prev = _tail->prev;
    _tail->prev->next = ptr;
    _tail->prev = ptr;
    _size++;
}

template <class T>
void list<T>::push_front(const value_type &value) {
    Node* ptr = new Node(value);
    ptr->prev = _root;
    ptr->next = _root->next;
    _root->next->prev = ptr;
    _root->next = ptr;
    _size++;
}

template <class T>
void list<T>::pop_back() {
    if (empty()) {
        throw std::length_error("list is empty");
    }
    Node *tmp = _tail->prev->prev;
    tmp->next = _tail;
    delete _tail->prev;
    _tail->prev = tmp;
    _size--;
}

template <class T>
void list<T>::pop_front() {
    if (empty()) {
        throw std::length_error("list is empty");
    }
    Node *tmp = _root->next->next;
    tmp->prev = _root;
    if (_root->next)
        delete _root->next;
    _root->next = tmp;
    _size--;
}

template <class T>
void list<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}


template <class T>
void list<T>::swap(list& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_root, other._root);
    std::swap(_tail, other._tail);
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
    Node *insertion = new Node(value);
    insertion->prev = pos.ptr->prev;
    insertion->next = pos.ptr;
    insertion->prev->next = insertion;
    insertion->next->prev = insertion;
    _size++;
    pos.ptr = pos.ptr->prev;
    iterator res = pos;
    return res;
}


template <class T>
void list<T>::erase(iterator pos) {
    if (pos.ptr == nullptr || pos.ptr->next == nullptr) {
        throw std::out_of_range("incorrect iterator");
    }
    Node *tmp = pos.ptr;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    delete tmp;
    _size--;
}

template <class T>
void list<T>::splice(const_iterator pos, list& other) {
    if (&other == this)
        return;
    if (_size == 0) {
        _root->next = other._root->next;
        _tail->prev = other._tail->prev;
    } else {
        pos.ptr->prev->next = other._root->next;
        other._root->next->prev = pos.ptr->prev;
    }
    other._tail->prev->next = pos.ptr;
    pos.ptr->prev = other._tail->prev;
    other._tail->prev = other._root;
    other._root->next = other._tail;
    _size += other._size;
    other._size = 0;
}

template <class T>
void list<T>::reverse() noexcept {
    iterator it = begin();
    while (it != end()) {
        std::swap(it.ptr->prev, it.ptr->next);
        --it;
    }
    std::swap(_root->prev, _root->next);
    std::swap(_tail->prev, _tail->next);
    std::swap(_root, _tail);
}

template <class T>
void list<T>::unique() {
    iterator iter = this->begin();
    while (iter != this->end()) {
        if (*iter == iter.ptr->next->data) {
            ++iter;
            this->erase(iter);
        } else {
            ++iter;
        }
    }
}

template <class T>
void list<T>::sort() {
    iterator First = begin();
    iterator Last = end();
    while (First != --Last)
            for (iterator i = First; i != Last; ++i)
                if ( i.ptr->next->data < *i )
                    std::swap(i.ptr->data, i.ptr->next->data);
}

template <class T>
void list<T>::merge(list& other) {
    if (&other == this)
        return;
    if (this->_size == 0) {
        this->splice(this->cend(), other);
        return;
    }
    iterator this_begin = this->begin();
    iterator other_begin = other.begin();
    size_type size_other = other._size;
    size_type size_this = _size;
    while (size_this && size_other) {
        if (*other_begin < *this_begin) {
            other._root->next = other._root->next->next;
            other_begin.ptr->next->prev = other._root;
            other_begin.ptr->next = this_begin.ptr;
            this_begin.ptr->prev->next = other_begin.ptr;
            this_begin.ptr->prev = other_begin.ptr;
            other_begin = other.begin();
            this_begin = this->begin();
            _size++;
            --other._size;
            --size_other;
        } else {
            ++this_begin;
            --size_this;
        }
    }
    this->splice(this->cend(), other);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos, Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    while (x < input_vector.end()) {
        insert(pos, *x);
        x += 1;
    }
    --pos;
    return pos;
}


template <class T>
template <typename... Args>
void list<T>::emplace_back(Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    while (x < input_vector.end()) {
        push_back(*x);
        x += 1;
    }
}

template <class T>
template <typename... Args>
void list<T>::emplace_front(Args&&... args) {
    std::vector<T> input_vector = { args... };
    auto x = input_vector.begin();
    while (x < input_vector.end()) {
        push_front(*x);
        x += 1;
    }
}
}  // namespace study