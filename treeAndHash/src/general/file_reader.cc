#include "file_reader.h"

namespace study {

// проверка строки матрицы на валидность
bool FileReader::StringCheck(const std::string& src) {
  bool result = true;
  std::istringstream s(src);
  std::vector<std::string> parced_line;
  std::string line;
  while (parced_line.size() < kMax && std::getline(s, line, ' ')) {
    parced_line.push_back(line);
  }
  // если строка неполная, то возвращаем ошибку
  if (parced_line.size() < kMax) {
    return false;
  }
  result &= NumCheck(parced_line[kBirth]);
  result &= NumCheck(parced_line[kBalance]);
  return result;
}

// считывание строки
record_t FileReader::StringRead(const std::string& src) {
  record_t result;
  // если была пустая строка - выходим без никто
  if (src.size() == kZero) {
    return result;
  }
  std::istringstream s(src);
  std::string line;
  std::getline(s, result.first, ' ');  // получаем ключ
  std::getline(s, result.second.student.surname, ' ');  // получаем имя
  std::getline(s, result.second.student.name, ' ');  // получаем фамилию
  std::getline(s, line, ' ');
  result.second.student.birth = std::stoi(line);  // получаем год рождения
  std::getline(s, result.second.student.city, ' ');  // получаем город
  std::getline(s, line, ' ');
  result.second.student.balance = std::stoi(line);  // получаем кол-во монет
  result.second.create_time = std::time(nullptr);  // время создания записи
  result.second.death_time = -1;                   // таймер смерти
  return result;
}

// получение одной записи
record_t FileReader::GetRecord(std::ifstream* file) {
  std::string line;
  std::getline(*file, line, '\n');
  if (line.size() != kZero && !StringCheck(line)) {
    throw std::invalid_argument("ERROR: wrong arguments in the line: \"" +
                                line + "\"");
  }
  return StringRead(line);
}

}  // namespace study
