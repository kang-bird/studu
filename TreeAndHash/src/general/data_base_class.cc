#include "data_base_class.h"

namespace study {

// сравнение строки по масске
bool DataBaseClass::StringCompare(const std::string& input,
                                  const std::string& mask) {
  if (mask.size()) {
    return (input == mask);
  }
  return true;
}

// сравнение номера по маске
bool DataBaseClass::NumCompare(int input, int mask) {
  if (mask >= 0) {
    return (input == mask);
  }
  return true;
}

// сравнение записи по маске
bool DataBaseClass::MaskCompare(const student_t& input, const student_t& mask) {
  return StringCompare(input.name, mask.name) &&
         StringCompare(input.surname, mask.surname) &&
         StringCompare(input.city, mask.city) &&
         NumCompare(input.birth, mask.birth) &&
         NumCompare(input.balance, mask.balance);
}

//  копирование по маске строки
void DataBaseClass::StringUpdateStudent(std::string* input,
                                        const std::string& mask) {
  if (mask.size()) {
    *input = mask;
  }
}

//  копирование по маске числа
void DataBaseClass::NumUpdateStudent(int* input, int mask) {
  if (mask >= 0) {
    *input = mask;
  }
}

//  копирование по маске
void DataBaseClass::MaskUpdateStudent(student_t* input, const student_t& mask) {
  StringUpdateStudent(&(input->name), mask.name);
  StringUpdateStudent(&(input->surname), mask.surname);
  StringUpdateStudent(&(input->city), mask.city);
  NumUpdateStudent(&(input->birth), mask.birth);
  NumUpdateStudent(&(input->balance), mask.balance);
}

std::string DataBaseClass::StudentStringPreparing(const student_t& student) {
  std::string result = student.surname + " ";
  result += student.name + " ";
  result += std::to_string(student.birth) + " ";
  result += student.city + " ";
  result += std::to_string(student.balance);
  return result;
}

std::string DataBaseClass::RecordStringPreparing(const record_t& record) {
  std::string result = record.first + " ";
  result += StudentStringPreparing(record.second.student);
  return result;
}

// загрузка из файла
size_t DataBaseClass::Upload(const std::string& name) {
  size_t result = kZero;
  std::ifstream file(name);
  if (file) {
    Clear();
    while (!file.eof()) {
      record_t new_record = reader_.GetRecord(&file);
      if (new_record.first.size() != kZero) {
        result += Set(new_record);
      }
    }
    file.close();
  } else {
    throw std::invalid_argument("file do not exist");
  }
  return result;
}

void DataBaseClass::AddLifeKey(const record_t& record) {
  if (record.second.death_time != -1) {
    key_live_.push_back(
        {record.first, record.second.create_time + record.second.death_time});
  }
  UpdateStorage();
}

void DataBaseClass::UpdateStorage() {
  time_t cur_time = std::time(NULL);
  auto f = [&](const std::pair<key_t, time_t>& record) {
    if (record.second < cur_time) {
      DelElement(record.first);
      return true;
    }
    return false;
  };
  auto iter = std::remove_if(key_live_.begin(), key_live_.end(), f);
  key_live_.erase(iter, key_live_.end());
}

}  // namespace study
