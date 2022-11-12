#ifndef SRC_HASH_TABLE_HASH_H_
#define SRC_HASH_TABLE_HASH_H_

#include "../general/data_base_class.h"

namespace study {
class HashTable : public DataBaseClass {
 private:
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

 private:  // Дополнительные функции
  record_t* GetElement(const key_t& key);
  size_t HashFunction(const key_t& key);
  bool Empty();
  bool DelElement(const key_t& key) override;

 private:
  const static size_t size_table_ = 10000;
  std::array<std::list<record_t>, size_table_> table_;
};
}  // namespace study

#endif  // SRC_HASH_TABLE_HASH_H_
