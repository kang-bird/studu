/*Балансируемое дерево было сделано по статье из habr
https://habr.com/ru/post/150732/
*/

#ifndef SRC_AVL_SELF_BALANCING_BINARY_SEARCH_TREE_H_
#define SRC_AVL_SELF_BALANCING_BINARY_SEARCH_TREE_H_

#include "../general/data_base_class.h"

namespace study {
class SelfBalancingBinarySearchTree : public DataBaseClass {
  using node_t = AVLNode;  // для этого класса node всегда AVLNode
  using func_t = std::function<void(node_t*)>;  // тип лямбда функции
  using func_key_t = std::function<void(node_t**)>;  // при сравнении ключа

 public:
  SelfBalancingBinarySearchTree(){};
  SelfBalancingBinarySearchTree(const AVL& other) { *this = other; };
  SelfBalancingBinarySearchTree(AVL&& other) { *this = other; };
  ~SelfBalancingBinarySearchTree() { DelTree(); }
  const AVL& operator=(const AVL&);
  const AVL& operator=(AVL&&);

  bool ExportToDot(const std::string&);
  bool TreeBalanceCheck();  // проверка сбалансированности дерева

 private:
  /* --БЛОК ФУНКЦИЙ БД-- */
  bool Set(const record_t&) override;
  void Get(const key_t&) override;
  bool Exist(const key_t&) override;
  bool Del(const key_t&) override;
  bool Update(const record_t&) override;
  void Keys() override;
  bool Rename(const key_t&, const key_t&) override;
  int TTL(const key_t&) override;
  void Find(const student_t&) override;
  void ShowAll() override;
  size_t Export(const std::string&) override;
  void Clear() override;

  /* --БЛОК ОСНОВНЫХ ФУНКЦИЙ РАБОТЫ С ДЕРЕВОМ-- */
  node_t* CreateNode(const record_t&);  // создание ноды
  node_t* FindLeft(node_t*);  //  ищем совпадающую ноду
  node_t* FindLast(const record_t&);  // поиск последней ноды для вставки
  node_t* FindEqualNode(const key_t&);  //  ищем совпадающую ноду
  void Traveling(node_t*, func_t);  // прохождение по дереву
  void TravelingWithKey(node_t**, const key_t&, func_key_t);  // с сравнением

  /* --БЛОК БАЛАНСИРОВКИ-- */
  unsigned char Height(node_t*);  // получаем высоту
  void FixHeight(node_t*);        // фиксируем высоты
  int BFactor(node_t*);           // получаем дельту высот
  node_t* RotateRight(node_t*);   // поворот вправо
  node_t* RotateLeft(node_t*);    // поворот влево
  node_t* Balance(node_t*);       // балансировка
  void FullWayBalance(node_t*);  // балансировка по всему пути до ноды
  void RootCheck(node_t*, node_t*);  // переопределение корня

  /* --БЛОК ОЧИСТКИ-- */
  void SetParent(node_t*, node_t*);
  void DelElementRight(node_t*, node_t*);
  void DelElementLeft(node_t*, node_t*);
  void DelElementAlone(node_t*, node_t*);
  bool DelElement(const key_t& key) override;  // удаление элемента
  void DelTree();
  std::string LineForming(const std::string&, const std::string&);

 private:
  node_t* root_ = nullptr;
};

}  // namespace study

#endif  // SRC_AVL_SELF_BALANCING_BINARY_SEARCH_TREE_H_
