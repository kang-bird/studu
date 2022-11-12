#include "types.h"

namespace study {
// проверяем число
bool NumCheck(const std::string& line) {
  bool result = true;
  // если значения невалидны выводим исключение
  try {
    result &= std::stoi(line) >= 0;
  } catch (std::invalid_argument const& ex) {
    std::cout << "ERROR: unable to cast value \"" << line << "\" to type int\n";
    result = false;
  }
  return result;
}

void PrintStringResult(const std::string& str) {
  Color color_text;
  std::cout << color_text.Rize(str, "White", "Black") << std::endl;
}

}  // namespace study
