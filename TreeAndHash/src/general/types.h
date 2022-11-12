#ifndef SRC_GENERAL_TYPES_H_
#define SRC_GENERAL_TYPES_H_
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <array>
#include <list>

#include "../interface/color.h"

const size_t kZero = 0;

namespace study {

class FileReader;     // класс чтения файлов
class DataBaseClass;  // базовый класс БД, родитель
class MainWindow;     // класс интерфейса
class SelfBalancingBinarySearchTree;  // класс бинарного дерева
struct Person;  // структура записи персонала
struct RecordValue;  // структура записи в БД
struct AVLNode;  // нода дерева AVL

using key_t = std::string;  // тип ключа записи
using student_t = Person;  // тип записи студента
using value_t = RecordValue;  // тип записи студента
using record_t = std::pair<key_t, value_t>;  // тип записи БД
using AVL = SelfBalancingBinarySearchTree;  // чтобы в глазах не мельтишило

// перечисление выбрано, чтобы верно ориентирвоаться в векторах
enum PersonParts {
  kKey = 0,
  kName = 1,
  kSurname,
  kBirth,
  kCity,
  kBalance,
  kMax,  // для определения числа элементов
};

// структура записи персонала
struct Person {
  std::string name;
  std::string surname;
  int birth = 0;
  std::string city;
  int balance = 0;
};

// значение записи, разделено на запись о студенте и метаданные о жизни
struct RecordValue {
  student_t student;
  time_t create_time = 0;
  int death_time = -1;
};

// нода дерева
struct AVLNode {
  record_t record;
  AVLNode* left = nullptr;
  AVLNode* right = nullptr;
  AVLNode* parent = nullptr;
  unsigned char height = 1;  // высота
};

bool NumCheck(const std::string& line);
void PrintStringResult(const std::string& str);

}  // namespace study

#endif  // SRC_GENERAL_TYPES_H_
