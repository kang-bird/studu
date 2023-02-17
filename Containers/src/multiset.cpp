#include "multiset.h"

namespace study {
/* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
template <class K>
multiset<K>::multiset() {
    this->_root = nullptr;
    this->_size = 0;
}

template <class K>
multiset<K>::multiset(std::initializer_list<value_type> const &items) : multiset() {
    auto x = items.begin();
    while (x < items.end()) {
        this->insert(*x);
        x += 1;
    }
}

template <class K>
multiset<K>::multiset(const multiset &s) : multiset() {
    this->tree_cpy(s._root, this);
}

template <class K>
multiset<K>::multiset(multiset &&s) : multiset() {
    if (this->_root != s._root) {
        std::swap(this->_root, s._root);
        std::swap(this->_size, s._size);
    }
}

template <class K>
multiset<K>::~multiset() {
    this->tree_del(&this->_root);
    this->_size = 0;
}

template <class K>
multiset<K>& multiset<K>::operator=(multiset &&s) {
    this->tree_del(&this->_root);
    this->_size = 0;
    std::swap(this->_root, s._root);
    std::swap(this->_size, s._size);
    return *this;
}
/* ----------------------------------------------- */

// сравнение, сделано для наследования multiset
template <class K>
bool multiset<K>::insert_check(K value, K key) {
    return value >= key;
}


// вставка элемента
template <class K>
typename multiset<K>::iterator multiset<K>::insert(const_reference value) {
    // подготовливаем переменные для возврата
    iterator iter;
    // если это первый элемент, тогда создаём корень
    if (this->_root == nullptr) {
        this->_root = new rb_tree<K>(value, nullptr, nullptr, nullptr);
        // присваиваем позицию итератору
        iter._pos = this->_root;
        this->_root->parent = nullptr;
        this->_size += 1;
    } else {
        // ищем крайнюю позицию
        rb_tree<K> *c_node = this->find_new_pos(value);
        // создаём элемент с указанием родителем ранее найденного
        rb_tree<K> *n_node = new rb_tree<K>(value, c_node, nullptr, nullptr);
        if (n_node != nullptr) {
            // присваиваем позицию итератору
            iter._pos = n_node;
            if (value < c_node->key) {
                c_node->left = n_node;
            } else if (insert_check(value, c_node->key)) {
                c_node->right = n_node;
            }
            this->_size += 1;
        }
    }
    // запоминаем корень дерева
    iter._iter_root = this->_root;
    return iter;
}

template <class K>
void multiset<K>::merge(multiset& other) {
    // избавляемся от лишней работы
    if (this->_root != other._root) {
        this->tree_merg(other._root);
        other.clear();
    }
}


// подсчёт совпадающих элементов
template <class K>
typename multiset<K>::size_type  multiset<K>::count(const K& key) {
    size_type result = 0;
    size_type x = 0;
    iterator iter = this->begin();
    while (x < this->_size) {
        if (*iter == key)
            result += 1;
        ++iter;
        x += 1;
    }
    return result;
}

// поиск диапазона
template <class K>
typename multiset<K>::iter_pair  multiset<K>::equal_range(const K& key) {
    return { lower_bound(key), upper_bound(key)};
}

// поиск первого элемента большего и равного ключу
template <class K>
typename multiset<K>::iterator  multiset<K>::lower_bound(const K& key) {
    iterator iter = this->begin();
    iterator result = this->end();
    size_type x = this->size();
    bool done = false;
    while (x > 0 && !done) {
        if (*iter >= key) {
            result = iter;
            done = true;
        }
        ++iter;
        x -= 1;
    }
    return result;
}

// поиск первого элемента большего чем ключ
template <class K>
typename multiset<K>::iterator  multiset<K>::upper_bound(const K& key) {
    iterator iter = this->begin();
    iterator result = this->end();
    size_type x = this->size();
    bool done = false;
    while (x > 0 && !done) {
        if (*iter > key) {
            result = iter;
            done = true;
        }
        ++iter;
        x -= 1;
    }
    return result;
}
}  // namespace study