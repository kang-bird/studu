#include "map.h"

namespace study {

/* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
template <class K, class M>
map<K, M>::map(std::initializer_list<value_type> const &items) {
    auto x = items.begin();
    while (x < items.end()) {
        insert(*x);
        x += 1;
    }
}

template <class K, class M>
map<K, M>& map<K, M>::operator=(map &&m) {
    _value = std::move(m._value);
    return *this;
}
/* ----------------------------------------------- */

/* --БЛОК ИЗМЕНЕНИЯ ЗНАЧЕНИЯ-- */
template <class K, class M>
M& map<K, M>::at(const K& key) {
    iterator iter = find(key);
    if (iter._pos == nullptr)
        throw std::out_of_range("AT, cant find key");
    return iter._pos->key.second;
}
/* ----------------------------------------------- */

/* --БЛОК ИЗМЕНЕНИЯ КОНТЕЙНЕРА-- */
template <class K, class M>
typename map<K, M>::insert_res map<K, M>::insert(const_reference value) {
    iterator iter = _value.end();
    insert_res result = { _value.end(), false };
    if (!contains(value.first))
        result = _value.insert(value);
    else
        result.first = find(value.first);
    return result;
}

template <class K, class M>
typename map<K, M>::insert_res map<K, M>::insert_or_assign(const K& key, const M& obj) {
    erase(find(key));
    return insert( { key, obj } );
}

template <class K, class M>
void map<K, M>::merge(map& other) {
    iterator iter = other.begin();
    size_type size = other.size();
    while (size > 0) {
        bool done = false;
        size -= 1;
        if (!contains((*iter).first)) {
            insert(*iter);
            other.erase(iter);
            size = other.size();
            iter = other.begin();
            done = true;
        }
        if (!done)
            ++iter;
    }
}

template <class K, class M>
template <class... Args>
typename map<K, M>::emplace_res map<K, M>::emplace(Args&&... args) {
    emplace_res result;
    std::vector<value_type> args_vector = { args... };
    auto x = args_vector.begin();
    while (x < args_vector.end()) {
        result.push_back(insert(*x));
        x += 1;
    }
    return result;
}
/* ----------------------------------------------- */

/* --БЛОК ПРОСМОТРА КОНТЕЙНЕРА-- */
template <class K, class M>
typename map<K, M>::iterator map<K, M>::find(const K& key) {
    iterator result = end();
    iterator iter = _value.begin();
    size_type size = _value.size();
    while (size > 0) {
        if (key == (*iter).first)
            result = iter;
        ++iter;
        size -= 1;
    }
    return result;
}

template <class K, class M>
bool map<K, M>::contains(const K& key) {
    bool result = false;
    iterator iter = _value.begin();
    size_type size = _value.size();
    while (size > 0) {
        result |= key == (*iter).first;
        ++iter;
        size -= 1;
    }
    return result;
}
/* ----------------------------------------------- */

// печать отсортированного дерева
template <class K, class M>
void map<K, M>::print(const char* name) {
    std::cout << name << '\n';
    std::cout << "Map size = " << size() << '\n';
    size_type x = 0;
    iterator iter = end();
    while (x < size()) {
        --iter;
        std::cout << "Key = " << (*iter).first;
        std::cout << " Obj = " << (*iter).second;
        if (iter._pos == iter._iter_root)
            std::cout << " ROOT";
        std::cout << "\tPos = " << iter._pos;
        if (iter._pos != nullptr) {
            std::cout << '\n';
            std::cout << "Parent = " << iter._pos->parent;
            std::cout << "\tLeft = " << iter._pos->left;
            std::cout << "\tRight = " << iter._pos->right;
        }
        std::cout << '\n';
        x += 1;
    }
    std::cout << '\n';
}
}  // namespace study