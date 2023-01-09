#include "types.h"

namespace study {

std::vector<std::string> ConvertFile(const std::string& name) {
    std::vector<std::string> result;
    std::ifstream file(name);
    if (file) {
        std::string line;
        while (!file.eof() && std::getline(file, line, '\n'))
            result.push_back(line);
        file.close();
    }
    return result;
}

void FilePrep(const std::string& name, size_t group, size_t count) {
    auto strings = ConvertFile(name);
    // считаем строк для каждой группы
    size_t str_count = strings.size();
    size_t str_test = str_count / group;
    // готовим временные файлы
    std::ofstream file_cross_learn(kNameLearn);
    std::ofstream file_test(kNameTest);
    size_t x = 0;
    while (x < str_count) {
        if (x < str_test * (count - 1) || x >= str_test * count) {
            file_cross_learn << strings[x] << '\n';
        } else {
            file_test << strings[x] << '\n';
        }
        x += 1;
    }
    file_cross_learn.close();
    file_test.close();
}

void FilePrepTest(const std::string& name, double percent) {
    auto strings = ConvertFile(name);
    size_t str_count = strings.size();
    size_t str_test = str_count * percent;
    std::ofstream file_test(kNameTest);
    size_t x = 0;
    while (x < str_test) {
        file_test << strings[x] << '\n';
        x += 1;
    }
    file_test.close();
}

}  // namespace study
