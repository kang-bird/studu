#ifndef SRC_SET_H_
#define SRC_SET_H_
#include "containers.h"

namespace study {

template <class K>
struct rb_tree{
    K key;
    rb_tree<K> *parent;
    rb_tree<K> *left;
    rb_tree<K> *right;
    rb_tree(K k, rb_tree<K> *p, rb_tree<K> *l, rb_tree<K> *r) : key(k), parent(p), left(l), right(r) {}
};

template <class K>
class set {
 public:
    class set_iter;
    /* --БЛОК ПЕРЕОПРЕДЕЛЕНИЯ ТИПОВ-- */
    using key_type = K;
    using value_type = K;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = set_iter;
    using const_iterator = const iterator;
    using size_type = size_t;
    using insert_res = std::pair<iterator, bool>;
    using emplace_res = std::vector<std::pair<iterator, bool>>;
    using node_type = rb_tree<key_type>;
    /* ----------------------------------------------- */

    class set_iter {
     public:
        rb_tree<K> *_pos;
        rb_tree<K> *_iter_root;

        set_iter();
        ~set_iter() {}
        const K& operator*();  // в дереве нельзя менять ключевые элементы
        set_iter& operator--();
        set_iter& operator++();
        bool operator==(const_iterator &i);
        bool operator!=(const_iterator &i);
    };

 protected:
    node_type *_root;
    size_type _size;
    /* ----------------------------------------------- */

    /* --БЛОК РАБОТЫ С ДЕРЕВОМ-- */
    node_type* find_new_pos(key_type key);
    node_type* find_left(node_type *tree);
    node_type* find_right(node_type *tree);
    void find_prev(node_type* tree,
                   node_type* cur_pos,
                   node_type** prev, int *flag);
    void find_next(node_type* tree,
                   node_type* cur_pos,
                   node_type** next, int *flag);
    void tree_cpy(node_type *tree, set *new_set);
    void tree_del(node_type **tree);
    void tree_merg(node_type *tree);
    bool tree_contains(node_type *tree, const_reference key);
    node_type* tree_find(node_type *tree, const_reference key);
    void sorting(node_type *tree);
    void size_recalc(node_type *tree);
    virtual bool insert_check(key_type value, key_type key);
    /* ----------------------------------------------- */

 public:
    /* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
    set();
    explicit set(std::initializer_list<value_type> const &items);
    set(const set &s);
    set(set &&s);
    ~set();
    set& operator=(set &&s);
    /* ----------------------------------------------- */

    /* --БЛОК ИТЕРАТОРОВ-- */
    iterator begin();
    iterator end();
    /* ----------------------------------------------- */

    /* --БЛОК ПРОВЕРКИ НАПОЛНЕНИЯ-- */
    bool empty();
    size_type size();
    size_type max_size();
    /* ----------------------------------------------- */

    /* --БЛОК ИЗМЕНЕНИЯ КОНТЕЙНЕРА-- */
    void clear();
    insert_res insert(const_reference value);
    void erase(iterator pos);
    void swap(set& other);
    void merge(set& other);
    template <class... Args>
    emplace_res emplace(Args&&... args);
    /* ----------------------------------------------- */

    /* --БЛОК ПРОСМОТРА КОНТЕЙНЕРА-- */
    iterator find(const_reference key);
    bool contains(const_reference key);
    /* ----------------------------------------------- */

    void print(const char* name);
};
}  // namespace study
#endif  // SRC_SET_H_
