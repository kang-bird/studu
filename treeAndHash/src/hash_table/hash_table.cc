#include "hash_table.h"

namespace study {

// Вставка в хэш таблицу
bool HashTable::Set(const record_t& record) {
  bool result = false;
  size_t num = HashFunction(record.first);
  if (!GetElement(record.first)) {
    AddLifeKey(record);
    table_[num].push_back(record);
    result = true;
  }
  return result;
}

// Получение элемента по ключу
void HashTable::Get(const key_t& key) {
  UpdateStorage();
  std::string result = "(null)";
  if (GetElement(key)) {
    result = StudentStringPreparing((GetElement(key)->second).student);
  }
  PrintStringResult(result);
}

// Проверка существует ли запись с заданным ключом
bool HashTable::Exist(const key_t& key) {
  UpdateStorage();
  bool result = false;
  if (GetElement(key)) result = true;
  return result;
}

// Удаление элемента
bool HashTable::Del(const key_t& key) {
  UpdateStorage();
  return DelElement(key);
}

// Удаление элемента
bool HashTable::DelElement(const key_t& key) {
  bool result = true;
  if (!GetElement(key)) {
    result = false;
  } else {
    size_t num = HashFunction(key);
    for (auto it = table_[num].begin(); it != table_[num].end(); it++) {
      if ((*it).first == key) {
        table_[num].erase(it);
        break;
      }
    }
  }
  return result;
}

// Получения всех записей
void HashTable::ShowAll() {
  UpdateStorage();
  if (!Empty()) {
    size_t count = kZero;
    for (size_t i = 0; i < size_table_; i++) {
      std::for_each(
          table_[i].begin(), table_[i].end(), [&](const record_t& record) {
            count += 1;
            PrintStringResult(std::to_string(count) + ") " +
                              StudentStringPreparing(record.second.student));
          });
    }
  } else {
    PrintStringResult("Empty");
  }
}

// Просмотр оставшегося времени
int HashTable::TTL(const key_t& key) {
  UpdateStorage();
  int result = -1;
  if (GetElement(key)) {
    value_t temp = GetElement(key)->second;
    time_t delta = std::time(nullptr) - temp.create_time;
    result = temp.death_time - static_cast<int>(delta);
  }
  return result;
}

// Переименовывает ключ
bool HashTable::Rename(const key_t& key_old, const key_t& key_new) {
  UpdateStorage();
  bool result = false;
  if (!GetElement(key_new) && GetElement(key_old)) {
    record_t new_record = *GetElement(key_old);
    new_record.first = key_new;
    Set(new_record);
    Del(key_old);
    result = true;
  }
  return result;
}

// Получение всех ключей
void HashTable::Keys() {
  UpdateStorage();
  if (!Empty()) {
    size_t count = kZero;
    for (size_t i = 0; i < size_table_; i++) {
      std::for_each(
          table_[i].begin(), table_[i].end(), [&](const record_t& record) {
            count += 1;
            PrintStringResult(std::to_string(count) + ") " + record.first);
          });
    }
  } else {
    PrintStringResult("Empty");
  }
}

// Обновляет значение по соответствующему ключу
bool HashTable::Update(const record_t& other) {
  UpdateStorage();
  bool result = false;
  record_t* record = GetElement(other.first);
  if (record) {
    MaskUpdateStudent(&(record->second.student), other.second.student);
    result = true;
  }
  return result;
}

// Поиск элементов по маске
void HashTable::Find(const student_t& mask) {
  UpdateStorage();
  size_t count = kZero;
  for (size_t i = 0; i < size_table_; i++) {
    std::for_each(
        table_[i].begin(), table_[i].end(), [&](const record_t& record) {
          if (MaskCompare(record.second.student, mask)) {
            count += 1;
            PrintStringResult(std::to_string(count) + ") " + record.first);
          }
        });
  }
  if (count == 0) PrintStringResult("(null)");
}

size_t HashTable::Export(const std::string& file_name) {
  UpdateStorage();
  size_t result = kZero;
  std::ofstream file(file_name);
  if (file) {
    for (size_t i = 0; i < size_table_; i++) {
      std::for_each(table_[i].begin(), table_[i].end(),
                    [&](const record_t& record) {
                      file << RecordStringPreparing(record) << "\n";
                      result++;
                    });
    }
  }
  return result;
}

// Отчистка хранилища
void HashTable::Clear() {
  for (size_t i = 0; i < size_table_; i++) {
    table_[i].clear();
  }
  ClearKeys();
}

/* --БЛОК ДОПОЛНИТЕЛЬНЫХ ФУНКЦИЙ-- */

// Проверка на пустоту таблицы
bool HashTable::Empty() {
  bool result = true;
  for (size_t i = 0; i < size_table_ && result; i++) {
    if (!table_[i].empty()) result = false;
  }
  return result;
}

// Хэш функция
size_t HashTable::HashFunction(const key_t& key) {
  return (std::hash<std::string>{}(key)) % size_table_;
}

// Получение элемента по ключу
record_t* HashTable::GetElement(const key_t& key) {
  record_t* result = nullptr;
  size_t position = HashFunction(key);
  for (auto it = table_[position].begin();
       it != table_[position].end() && (!result); ++it) {
    if ((*it).first == key) {
      result = &(*it);
    }
  }
  return result;
}

}  // namespace study
