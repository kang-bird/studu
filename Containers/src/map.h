#ifndef SRC_MAP_H_
#define SRC_MAP_H_
#include "set.h"

namespace study {

template <class K, class M>
class map {
 public:
    using key_type = K;
    using mapped_type = M;
    using value_type = std::pair<const K, M>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename study::set<value_type>::set_iter;
    using const_iterator = const iterator;
    using size_type = size_t;

    using const_key_ref = const key_type&;
    using const_map_ref = const mapped_type&;
    using insert_res = std::pair<iterator, bool>;
    using emplace_res = std::vector<std::pair<iterator, bool>>;

 protected:
    study::set<value_type> _value;

 public:
    /* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
    map() {}
    explicit map(std::initializer_list<value_type> const &items);
    map(const map &m) : _value(m._value) {}
    map(map &&m) : _value(std::move(m._value)) {}
    ~map() { _value.~set(); }
    map& operator=(map &&m);
    /* ----------------------------------------------- */

    /* --БЛОК ИЗМЕНЕНИЯ ЗНАЧЕНИЯ-- */
    M& at(const_key_ref key);
    M& operator[](const_key_ref key) {
        return at(key); }
    /* ----------------------------------------------- */

    /* --БЛОК ИТЕРАТОРОВ-- */
    iterator begin() { return _value.begin(); }
    iterator end() { return _value.end(); }
    /* ----------------------------------------------- */

    /* --БЛОК ПРОВЕРКИ НАПОЛНЕНИЯ-- */
    bool empty() { return _value.empty(); }
    size_type size() { return _value.size(); }
    size_type max_size() { return _value.max_size(); }
    /* ----------------------------------------------- */

    /* --БЛОК ИЗМЕНЕНИЯ КОНТЕЙНЕРА-- */
    void clear() { _value.clear(); }
    insert_res insert(const_reference value);
    insert_res insert(const_key_ref key, const_map_ref obj) { return insert({ key, obj }); }
    insert_res insert_or_assign(const_key_ref key, const_map_ref obj);
    void erase(iterator pos) { _value.erase(pos); }
    void swap(map& other) { _value.swap(other._value); }
    void merge(map& other);
    template <class... Args>
    emplace_res emplace(Args&&... args);
    /* ----------------------------------------------- */

    /* --БЛОК ПРОСМОТРА КОНТЕЙНЕРА-- */
    iterator find(const_key_ref key);
    bool contains(const_key_ref key);
    /* ----------------------------------------------- */
    void print(const char* name);
};
}  // namespace study

#endif  // SRC_MAP_H_
