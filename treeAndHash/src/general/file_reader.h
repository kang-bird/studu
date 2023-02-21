#ifndef SRC_GENERAL_FILE_READER_H_
#define SRC_GENERAL_FILE_READER_H_

#include "types.h"

namespace study {
class FileReader {
 public:
  record_t GetRecord(std::ifstream* file);  // открытие файла

 private:
  /* -------ОТКРЫТИЕ ФАЙЛА------- */
  bool StringCheck(const std::string& src);  // проверка строки на валидность
  bool FileCheck(const std::string& name);  // проверка файла на валидность
  record_t StringRead(const std::string& src);  // считывание строки
};
}  // namespace study

#endif  // SRC_GENERAL_FILE_READER_H_
