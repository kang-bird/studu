#include "self_balancing_binary_search_tree.h"

namespace study {

const AVL& AVL::operator=(const AVL& other) {
  DelTree();
  // формируем функцию
  auto f = [this](node_t* node) { Set(node->record); };
  // запускаем в путешествие
  Traveling(other.root_, f);
  key_live_ = other.key_live_;
  return *this;
}

const AVL& AVL::operator=(AVL&& other) {
  DelTree();
  std::swap(root_, other.root_);
  key_live_ = std::move(other.key_live_);
  return *this;
}

/* --БЛОК ОСНОВНЫХ ФУНКЦИЙ РАБОТЫ С ДЕРЕВОМ-- */
// выделяем память для ноды
typename AVL::node_t* AVL::CreateNode(const record_t& other) {
  node_t* result = nullptr;
  result = new node_t;
  result->record = other;
  result->height = 1;
  return result;
}

// находим самую левую ноду
typename AVL::node_t* AVL::FindLeft(node_t* node) {
  node_t* result = nullptr;
  while (node) {
    result = node;
    node = node->left;
  }
  return result;
}

// находим последнюю ноду для вставки
typename AVL::node_t* AVL::FindLast(const record_t& other) {
  node_t* result = nullptr;
  node_t* chield = root_;
  // безрекурсионный обход дерева на поиск последней доступной ноды
  while (chield) {
    result = chield;
    if (other.first < result->record.first) {
      chield = result->left;
    } else if (other.first > result->record.first) {
      chield = result->right;
    } else {
      result = nullptr;
      chield = nullptr;
    }
  }
  return result;
}

// нахождение ноды с аналогичным ключом
typename AVL::node_t* AVL::FindEqualNode(const key_t& other) {
  node_t* result = nullptr;
  // формируем функцию
  auto f = [&other, &result](node_t** node) {
    if (!result && other == (*node)->record.first) {
      result = (*node);
    }
  };
  // запускаем в путешествие
  TravelingWithKey(&root_, other, f);
  return result;
}

// рекурсионный пробег по нодам
void AVL::Traveling(node_t* node, func_t f) {
  if (node) {
    Traveling(node->left, f);
    Traveling(node->right, f);
    f(node);
  }
}

// рекурсионное прохождение по дереву с сравнением
void AVL::TravelingWithKey(node_t** node, const key_t& other, func_key_t f) {
  if (node && *node) {
    if (other < (*node)->record.first) {
      TravelingWithKey(&((*node)->left), other, f);
    }
    if (other > (*node)->record.first) {
      TravelingWithKey(&((*node)->right), other, f);
    }
    f(node);
  }
}

/* --БЛОК БАЛАНСИРОВКИ-- */
// получаем высоту
unsigned char AVL::Height(node_t* node) {
  if (!node) {
    return kZero;
  }
  return node->height;
}

// фиксируем высоты
void AVL::FixHeight(node_t* node) {
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
}

// получаем дельту высот
int AVL::BFactor(node_t* node) {
  return Height(node->right) - Height(node->left);
}

// поворот вправо, для понимания см. статью из заголовочного
typename AVL::node_t* AVL::RotateRight(node_t* node) {
  node_t* node_new = node->left;
  node_new->parent = node->parent;
  node->left = node_new->right;
  if (node->left) {
    node->left->parent = node;
  }
  node_new->right = node;
  node->parent = node_new;
  FixHeight(node);
  FixHeight(node_new);
  return node_new;
}

// поворот влево, для понимания см. статью из заголовочного
typename AVL::node_t* AVL::RotateLeft(node_t* node) {
  node_t* node_new = node->right;
  node_new->parent = node->parent;
  node->right = node_new->left;
  if (node->right) {
    node->right->parent = node;
  }
  node_new->left = node;
  node->parent = node_new;
  FixHeight(node);
  FixHeight(node_new);
  return node_new;
}

// балансировка
typename AVL::node_t* AVL::Balance(node_t* node) {
  FixHeight(node);
  if (BFactor(node) == 2) {
    if (BFactor(node->right) < 0) {
      node->right = RotateRight(node->right);
    }
    return RotateLeft(node);
  }
  if (node && BFactor(node) == -2) {
    if (BFactor(node->left) > 0) {
      node->left = RotateLeft(node->left);
    }
    return RotateRight(node);
  }
  return node;
}

// балансировка по всему пути до ноды
void AVL::FullWayBalance(node_t* node) {
  auto f = [this](node_t** node) { *node = Balance(*node); };
  while (node) {
    TravelingWithKey(&root_, node->record.first, f);
    node = node->parent;
  }
}

// переопределение корня, используется при удалении
void AVL::RootCheck(node_t* finded, node_t* new_root) {
  if (root_ == finded) {
    root_ = new_root;
    if (root_) {
      root_->parent = nullptr;
    }
  }
}

/* --БЛОК ФУНКЦИЙ БД-- */
// вставка в дерево
bool AVL::Set(const record_t& other) {
  if (!root_) {
    AddLifeKey(other);
    root_ = CreateNode(other);
    return true;
  }
  UpdateStorage();
  node_t* cur_node = FindLast(other);
  if (cur_node) {
    AddLifeKey(other);
    if (other.first < cur_node->record.first) {
      cur_node->left = CreateNode(other);
      cur_node->left->parent = cur_node;
      FullWayBalance(cur_node->left);
    } else {
      cur_node->right = CreateNode(other);
      cur_node->right->parent = cur_node;
      FullWayBalance(cur_node->right);
    }
    return true;
  }
  return false;
}

// вставка в дерево
void AVL::Get(const key_t& other) {
  UpdateStorage();
  node_t* finded_node = FindEqualNode(other);
  std::string result = "(null)";
  if (finded_node) {
    result = StudentStringPreparing(finded_node->record.second.student);
  }
  PrintStringResult(result);
}

// существует ли ключ
bool AVL::Exist(const key_t& other) {
  UpdateStorage();
  if (FindEqualNode(other)) {
    return true;
  }
  return false;
}

// удаление ноды
bool AVL::Del(const key_t& other) {
  UpdateStorage();
  return DelElement(other);
}

// изменение записи по ключу
bool AVL::Update(const record_t& other) {
  UpdateStorage();
  node_t* finded_node = FindEqualNode(other.first);
  if (finded_node) {
    MaskUpdateStudent(&(finded_node->record.second.student),
                      other.second.student);
    return true;
  }
  return false;
}

// вывод всех ключей
void AVL::Keys() {
  if (root_) {
    size_t count = kZero;
    auto f = [&count](node_t* node) {
      count += 1;
      PrintStringResult(std::to_string(count) + ") " + node->record.first);
    };
    Traveling(root_, f);
  } else {
    PrintStringResult("Empty");
  }
}

// смена ключа
bool AVL::Rename(const key_t& dst, const key_t& src) {
  UpdateStorage();
  node_t* finded_node_dst = FindEqualNode(dst);
  node_t* finded_node_src = FindEqualNode(src);
  if (finded_node_dst && !finded_node_src) {
    // создаём запись с новым ключём
    record_t record = finded_node_dst->record;
    record.first = src;
    // возращаем результат удаления текущую записи и формирования новой
    return Del(dst) && Set(record);
  }
  return false;
}

// таймер смерти
int AVL::TTL(const key_t& other) {
  UpdateStorage();
  node_t* finded_node = FindEqualNode(other);
  if (finded_node) {
    time_t delta = std::time(nullptr) - finded_node->record.second.create_time;
    return (finded_node->record.second.death_time - static_cast<int>(delta));
  }
  return -1;
}

// вывод всех ключей
void AVL::Find(const student_t& mask) {
  UpdateStorage();
  if (root_) {
    size_t count = kZero;
    // задаём функцию сравнения по маске
    auto f = [this, mask, &count](node_t* node) {
      if (MaskCompare(node->record.second.student, mask)) {
        count += 1;
        PrintStringResult(std::to_string(count) + ") " + node->record.first);
      }
    };
    // запускаем в путешествие
    Traveling(root_, f);
  } else {
    PrintStringResult("(null)");
  }
}

// вывод всех записей
void AVL::ShowAll() {
  UpdateStorage();
  if (root_) {
    size_t count = kZero;
    // задаём функцию формирования строки записи
    auto f = [this, &count](node_t* node) {
      count += 1;
      PrintStringResult(std::to_string(count) + ") " +
                        StudentStringPreparing(node->record.second.student));
    };
    // запускаем в путешествие
    Traveling(root_, f);
  } else {
    PrintStringResult("Empty");
  }
}

// сохранение в файл
size_t AVL::Export(const std::string& name) {
  UpdateStorage();
  size_t result = kZero;
  std::ofstream file(name);
  if (file) {
    // задаём передачи записи в файл
    auto f = [this, &file, &result](node_t* node) {
      result += 1;
      file << RecordStringPreparing(node->record) << "\n";
    };
    // запускаем в путешествие
    Traveling(root_, f);
  }
  return result;
}

// сохранение в dot  файл
bool AVL::ExportToDot(const std::string& name) {
  std::ofstream file(name + ".dot");
  if (file) {
    file << "digraph { node [margin=0 fontsize=8 width=0 shape=circle]\n";
    // задаём функцию фомирования строк для файла
    auto f = [this, &file](node_t* node) {
      std::string null_style = " [color=black, style=filled, fontsize=2]";
      if (node->left) {
        file << LineForming(node->record.first, node->left->record.first) +
                    "[label=\"" + node->left->parent->record.first +
                    "h= " + std::to_string(node->left->height) +
                    "\", fontsize=6]\n";
      } else {
        file << "l_" + node->record.first + null_style + "\n";
        file << LineForming(node->record.first, "l_" + node->record.first) +
                    "\n";
      }
      if (node->right) {
        file << LineForming(node->record.first, node->right->record.first) +
                    "[color=blue, label=\"" +
                    node->right->parent->record.first +
                    "h= " + std::to_string(node->right->height) +
                    "\", fontsize=6]\n";
      } else {
        file << "r_" + node->record.first + null_style + "\n";
        file << LineForming(node->record.first, "r_" + node->record.first) +
                    "\n";
      }
    };
    // запускаем в путешествие
    Traveling(root_, f);
    file << "}";
    file.close();
    return true;
  }
  return false;
}

// удаление дерева
void AVL::Clear() { DelTree(); }

// проверка сбалансированности дерева
bool AVL::TreeBalanceCheck() {
  auto f = [this](node_t* node) {
    // Исключение, чтобы прервать рекурсию при первой ошибке
    if ((node->left && node->right &&
         std::abs(node->left->height - node->right->height) > 1) ||
        (node->height !=
         std::max(Height(node->left), Height(node->right)) + 1)) {
      throw std::domain_error("Disbalance in tree, node " + node->record.first +
                              "\n");
    }
  };
  try {
    Traveling(root_, f);
  } catch (const std::exception& ex) {
    std::cout << ex.what();
    return false;
  }
  return true;
}

/* --БЛОК ОЧИСТКИ-- */

// задание родительской ноды
void AVL::SetParent(node_t* parent_node, node_t* chield_node) {
  if (chield_node) {
    chield_node->parent = parent_node;
  }
}

// перелинковка, когда у удаляемой ноды есть правая ветка
void AVL::DelElementRight(node_t* parent_node, node_t* finded_node) {
  // если выбранная нода является левой
  if (parent_node->left == finded_node) {
    // то её правую ветку передаём родителю влево
    parent_node->left = finded_node->right;
    SetParent(parent_node, parent_node->left);
  } else {
    // иначе вправо
    parent_node->right = finded_node->right;
    SetParent(parent_node, parent_node->right);
  }
  FullWayBalance(parent_node);
}

// перелинковка, когда у удаляемой ноды есть только лева ветка
void AVL::DelElementLeft(node_t* parent_node, node_t* finded_node) {
  // если выбранная нода является левой
  if (parent_node->left == finded_node) {
    // то её левую ветку передаём родителю влево
    parent_node->left = finded_node->left;
    SetParent(parent_node, parent_node->left);
  } else {
    // иначе вправо
    parent_node->right = finded_node->left;
    SetParent(parent_node, parent_node->right);
  }
  FullWayBalance(parent_node);
}

// перелинковка, когда у удаляемой ноды нет детей
void AVL::DelElementAlone(node_t* parent_node, node_t* finded_node) {
  // если выбранная нода является левой
  if (parent_node->left == finded_node) {
    // то зануляем левый указатель у родителя
    parent_node->left = nullptr;
  } else {
    parent_node->right = nullptr;
  }
  FullWayBalance(parent_node);
}

// удаление ноды
bool AVL::DelElement(const key_t& other) {
  node_t* finded_node = FindEqualNode(other);
  if (finded_node) {
    // находим самую левую ноду правой части для замены
    node_t* left_node = FindLeft(finded_node->right);
    // если найдена крайняя левая нода справа
    if (left_node) {
      // переносим запись
      finded_node->record = left_node->record;
      DelElementRight(left_node->parent, left_node);
      delete left_node;
      return true;
    }
    // если справа ничего нет, то смотрим влево
    if (finded_node->left) {
      if (finded_node->parent) {
        DelElementLeft(finded_node->parent, finded_node);
      } else {
        RootCheck(finded_node, finded_node->left);
      }
      delete finded_node;
      return true;
    }
    // если у ноды нет детей, то просто удаляем и зануляем указатель у родителя
    if (finded_node->parent) {
      DelElementAlone(finded_node->parent, finded_node);
    } else {
      RootCheck(finded_node, nullptr);
    }
    delete finded_node;
    return true;
  }
  return false;
}

/* удаление дерева, метод выделен отдельно,
поскольку нельзя в деструкторе вызывать
виртуальные методы, в нашем случае Clear() */
void AVL::DelTree() {
  if (root_) {
    // задаём функцию удаления ноды
    auto f = [](node_t* node) {
      delete node;
      node = nullptr;
    };
    // запускаем в путешествие
    Traveling(root_, f);
    root_ = nullptr;
  }
  ClearKeys();
}

// Формирование строки
std::string AVL::LineForming(const std::string& x, const std::string& y) {
  return "\t" + x + " -> " + y;
}

}  // namespace study
