#include "set.h"

namespace study {

/* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
template <class K>
set<K>::set() {
    _root = nullptr;
    _size = 0;
}

template <class K>
set<K>::set(std::initializer_list<value_type> const &items) : set() {
    auto x = items.begin();
    while (x < items.end()) {
        this->insert(*x);
        x += 1;
    }
}

template <class K>
set<K>::set(const set &s) : set() {
    tree_cpy(s._root, this);
}

template <class K>
set<K>::set(set &&s) : set() {
    if (_root != s._root) {
        std::swap(_root, s._root);
        std::swap(_size, s._size);
    }
}

template <class K>
set<K>::~set() {
    tree_del(&_root);
    _size = 0;
}

template <class K>
set<K>& set<K>::operator=(set &&s) {
    if (_root != s._root) {
        tree_del(&_root);
        _size = 0;
        std::swap(_root, s._root);
        std::swap(_size, s._size);
    }
    return *this;
}
/* ----------------------------------------------- */

/* --БЛОК РАБОТЫ С ДЕРЕВОМ-- */
// ищем место для нового элемента
template <class K>
rb_tree<K> *set<K>::find_new_pos(K key) {
    rb_tree<K> *result = _root;
    while ((result->left != nullptr && key < result->key) ||
           (result->right != nullptr && insert_check(key, result->key))) {
        if (key < result->key) {
            result = result->left;
        } else if (insert_check(key, result->key)) {
            result = result->right;
        }
    }
    return result;
}

// ищем самый левый элемент
template <class K>
rb_tree<K> *set<K>::find_left(rb_tree<K> *tree) {
    rb_tree<K> *result;
    if (tree != nullptr) {
        if (tree->left == nullptr)
            result = tree;
        else
            result = find_left(tree->left);
    } else {
        result = nullptr;
    }
    return result;
}

// ищем самый правый элемент
template <class K>
rb_tree<K> *set<K>::find_right(rb_tree<K> *tree) {
    rb_tree<K> *result;
    if (tree != nullptr) {
        if (tree->right == nullptr)
            result = tree;
        else
            result = find_right(tree->right);
    } else {
        result = nullptr;
    }
    return result;
}

// ищем ближайший меньший элемент
template <class K>
void set<K>::find_prev(rb_tree<K>* tree, rb_tree<K>* cur_pos, rb_tree<K>** prev, int *flag) {
    if (tree != nullptr) {
        find_prev(tree->right, cur_pos, prev, flag);
        if (*flag == 0 && cur_pos == tree) {
            *flag = 1;
        } else if (*flag == 1) {
            *prev = tree;
            *flag = 2;
        }
        find_prev(tree->left, cur_pos, prev, flag);
    }
}

// ищем ближайший больший элемент
template <class K>
void set<K>::find_next(rb_tree<K>* tree, rb_tree<K>* cur_pos, rb_tree<K>** next, int *flag) {
    if (tree != nullptr) {
        find_next(tree->left, cur_pos, next, flag);
        if (*flag == 0 && cur_pos == tree) {
            *flag = 1;
        } else if (*flag == 1) {
            *next = tree;
            *flag = 2;
        }
        find_next(tree->right, cur_pos, next, flag);
    }
}

// копирвоание дерева
template <class K>
void set<K>::tree_cpy(rb_tree<K> *tree, set *new_set) {
    if (tree != nullptr) {
        new_set->insert(tree->key);
        tree_cpy(tree->left, new_set);
        tree_cpy(tree->right, new_set);
    }
}
// печать дерева
template <class K>
void set<K>::sorting(rb_tree<K> *tree) {
    if (tree != nullptr) {
        sorting(tree->left);
        std::cout << tree->key << " ";
        sorting(tree->right);
    }
}
// удаление дерева
template <class K>
void set<K>::tree_del(rb_tree<K> **tree) {
    if (*tree != nullptr) {
        tree_del(&((*tree)->left));
        tree_del(&((*tree)->right));
        delete *tree;
        *tree = nullptr;
    }
}
// слияние деревьев
template <class K>
void set<K>::tree_merg(rb_tree<K> *tree) {
    if (tree != nullptr) {
        tree_merg(tree->left);
        tree_merg(tree->right);
        insert(tree->key);
    }
}

// проверка наличия элемента в дереве
template <class K>
bool set<K>::tree_contains(rb_tree<K> *tree, const K& key) {
    bool result = false;
    if (tree != nullptr) {
        if (tree->key == key)
            result = true;
        result |= tree_contains(tree->left, key) ||
                tree_contains(tree->right, key);
    }
    return result;
}

// пересчитываем размер дерева
template <class K>
void set<K>::size_recalc(rb_tree<K> *tree) {
    if (tree != nullptr) {
        size_recalc(tree->left);
        _size += 1;
        size_recalc(tree->right);
    }
}

// сравнение, сделано для наследования multiset
template <class K>
bool set<K>::insert_check(K value, K key) {
    return value > key;
}

// поиск позиции элемента в дереве
template <class K>
rb_tree<K>* set<K>::tree_find(rb_tree<K> *tree, const K& key) {
    rb_tree<K> *result = nullptr;
    if (tree != nullptr) {
        if (tree->key == key)
            result = tree;
        else if (tree_contains(tree->left, key))
            result = tree_find(tree->left, key);
        else if (tree_contains(tree->right, key))
            result = tree_find(tree->right, key);
    }
    return result;
}

// печать отсортированного дерева
template <class K>
void set<K>::print(const char* name) {
    std::cout << name << '\n';
    std::cout << "Size = " << this->size() << " _root pointer " << _root <<'\n';
    sorting(_root);
    std::cout << '\n';
}
/* ----------------------------------------------- */

/* --БЛОК ИТЕРАТОРОВ-- */
// конструктор итератора
template <class K>
set<K>::set_iter::set_iter() {
    _pos = nullptr;
    _iter_root = nullptr;
}

// разыименовывание итератора
template <class K>
const K& set<K>::set_iter::operator*() {
    if (_pos == nullptr)
        throw std::range_error("null iterator");
    return _pos->key;
}

// проверка равности итераторов
template <class K>
bool set<K>::set_iter::operator==(const_iterator &i) {
    return (_pos == i._pos && _iter_root == i._iter_root);
}

// переход к предыдущему элементу
template <class K>
typename set<K>::iterator& set<K>::set_iter::operator--() {
    set func_set;
    if (_pos == nullptr) {
        _pos = func_set.find_right(_iter_root);
    } else if (_pos != func_set.find_left(_iter_root)) {
        rb_tree<K>* prev = nullptr;
        int flag = 0;
        func_set.find_prev(_iter_root, _pos, &prev, &flag);
        if (prev != nullptr)
            _pos = prev;
    }
    return *this;
}

// переход к следующему элементу
template <class K>
typename set<K>::iterator& set<K>::set_iter::operator++() {
    set func_set;
    if (_pos == nullptr) {
        _pos = func_set.find_left(_iter_root);
    } else {
        rb_tree<K>* next = nullptr;
        int flag = 0;
        func_set.find_next(_iter_root, _pos, &next, &flag);
            _pos = next;
    }
    return *this;
}

// проверка равности итераторов
template <class K>
bool set<K>::set_iter::operator!=(const_iterator &i) {
    return !(*this == i);
}

// первый (наименьший) элемент
template <class K>
typename set<K>::iterator set<K>::begin() {
    iterator result;
    result._pos = find_left(_root);
    result._iter_root = _root;
    return result;
}

// последний (наибольший) элемент
template <class K>
typename set<K>::iterator set<K>::end() {
    iterator result;
    result._pos = nullptr;
    result._iter_root = _root;
    return result;
}

/* ----------------------------------------------- */

/* --БЛОК ПРОВЕРКИ НАПОЛНЕНИЯ-- */

template <class K>
bool set<K>::empty() {
    return (nullptr == _root);
}

template <class K>
typename set<K>::size_type set<K>::size() {
    return _size;
}

template <class K>
typename set<K>::size_type set<K>::max_size() {
    return std::numeric_limits<size_type>::max() / (sizeof(rb_tree<value_type>));
}
/* ----------------------------------------------- */

/* --БЛОК ИЗМЕНЕНИЯ КОНТЕЙНЕРА-- */
// очистка дерева
template <class K>
void set<K>::clear() {
    tree_del(&_root);
    _size = 0;
}

// вставка элемента
template <class K>
typename set<K>::insert_res set<K>::insert(const_reference value) {
    // подготовливаем переменные для возврата
    iterator iter;
    bool result_bool = true;
    // если это первый элемент, тогда создаём корень
    if (_root == nullptr) {
        _root = new rb_tree<K>(value, nullptr, nullptr, nullptr);
        // присваиваем позицию итератору
        iter._pos = _root;
        _root->parent = nullptr;
        _size += 1;
    } else {
        // ищем крайнюю позицию
        rb_tree<K> *c_node = find_new_pos(value);
        // создаём элемент с указанием родителем ранее найденного
        rb_tree<K> *n_node = new rb_tree<K>(value, c_node, nullptr, nullptr);
        if (n_node != nullptr) {
            // присваиваем позицию итератору
            iter._pos = n_node;
            if (value < c_node->key) {
                c_node->left = n_node;
                _size += 1;
            } else if (insert_check(value, c_node->key)) {
                c_node->right = n_node;
                _size += 1;
            } else {
                result_bool = false;
                delete n_node;
            }
        } else {
            result_bool = false;
        }
    }
    // запоминаем корень дерева
    iter._iter_root = _root;
    insert_res result = { iter, result_bool };
    return result;
}

// удаление одного элемента
template <class K>
void set<K>::erase(iterator pos) {
    rb_tree<K>* tree = pos._pos;
    if (tree != nullptr) {
        rb_tree<K>* pos_left = tree->left;
        rb_tree<K>* pos_right = tree->right;
        if (tree != _root) {
            if (tree->parent->left == tree) {
                tree->parent->left = nullptr;
            }
            if (tree->parent->right == tree) {
                tree->parent->right = nullptr;
            }
            tree_cpy(pos_left, this);
            tree_cpy(pos_right, this);
            tree_del(&tree);
        } else {
            // назначем левую ветку корнем
            _root = pos_left;
            // обнуляем родителя у корня
            if (_root != nullptr)
                _root->parent = nullptr;
            // обрезаем левую ветку у дреа, чтобы не удалилось
            tree->left = nullptr;
            // копируем правую ветку
            tree_cpy(pos_right, this);
            // удаляем дерево
            tree_del(&tree);
        }
        _size = 0;
        size_recalc(_root);
    }
}

// обмен данными между контейнерами
template <class K>
void set<K>::swap(set& other) {
    std::swap(_root, other._root);
    std::swap(_size, other._size);
}

// слияние двух контейнеров
template <class K>
void set<K>::merge(set& other) {
    iterator iter = other.begin();
    size_type size = other.size();
    while (size > 0) {
        bool done = false;
        size -= 1;
        if (!contains(*iter)) {
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

// вставка нескольких элементов
template <class K>
template <class... Args>
typename set<K>::emplace_res set<K>::emplace(Args&&... args) {
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

// наличие элемента в контейнере
template <class K>
bool set<K>::contains(const K& key) {
    return tree_contains(_root, key);
}

// поиск позиции элемента в контейнере
template <class K>
typename set<K>::iterator set<K>::find(const K& key) {
    set<K>::iterator result;
    result._pos = tree_find(_root, key);
    result._iter_root = _root;
    return result;
}
}  // namespace study
/* ----------------------------------------------- */
