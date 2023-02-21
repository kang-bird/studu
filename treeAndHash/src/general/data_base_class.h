#ifndef SRC_GENERAL_DATA_BASE_CLASS_H_
#define SRC_GENERAL_DATA_BASE_CLASS_H_

#include "file_reader.h"

namespace study {
class DataBaseClass {
 public:
  virtual bool Set(const record_t&) = 0;
  virtual void Get(const key_t&) = 0;
  virtual bool Exist(const key_t&) = 0;
  virtual bool Del(const key_t&) = 0;
  virtual bool Update(const record_t&) = 0;
  virtual void Keys() = 0;
  virtual bool Rename(const key_t&, const key_t&) = 0;
  virtual int TTL(const key_t&) = 0;
  virtual void Find(const student_t&) = 0;
  virtual void ShowAll() = 0;
  size_t Upload(const std::string&);
  virtual size_t Export(const std::string&) = 0;
  virtual void Clear() = 0;  // очистка БД

 protected:
  bool StringCompare(const std::string&,
                     const std::string&);  // сравнение строк
  bool NumCompare(int input, int mask);    // сравнение чисел
  bool MaskCompare(const student_t&, const student_t&);  //  сравнение по маске
  void StringUpdateStudent(std::string* input,
                           const std::string& mask);  // копирование строки
  void NumUpdateStudent(int* input, int mask);  // копирование числа
  void MaskUpdateStudent(student_t* input,
                         const student_t& mask);  //  копирование по маске
  virtual bool DelElement(const key_t& key) = 0;

  std::string StudentStringPreparing(const student_t&);
  std::string RecordStringPreparing(const record_t& record);

  void AddLifeKey(const record_t& record);
  void ClearKeys() { key_live_.clear(); }
  void UpdateStorage();

 protected:
  std::vector<std::pair<key_t, time_t>> key_live_;
  FileReader reader_;
};
}  // namespace study

#endif  // SRC_GENERAL_DATA_BASE_CLASS_H_
