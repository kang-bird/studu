#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <gtkmm.h>
#include <iostream>
#include <filesystem>

namespace study {
//  классы графового прецептрона
class GraphNeuron;
class GraphLayer;
class GraphPreceptron;
//  класс матричного прецептрона
class MatrixModel;
// классы паттерна Стратегия
class Strategy;
class MatrixStrategy;
class GraphStrategy;
//  класс контроллера
class Controller;
//  класс объекта визуализации
class MainWindow;

const size_t kNeuronInValue = 784;  // кол-во нейронов в входном слое
const size_t kNeuronHValue = 128;  // кол-во нейронов в скрытых слоях
const size_t kNeuronOutValue = 26;  // кол-во нейронов в выходном слое
const double kLearningRate = 0.1;  // скорость обучаемости
const char kNameLearn[] = "temp_learn.csv";
const char kNameTest[] = "temp_test.csv";

using income_t = std::array<double, kNeuronInValue>;
using result_t = std::array<double, kNeuronOutValue>;

std::vector<std::string> ConvertFile(const std::string& name);  // конвертация файла в вектор строк
void FilePrep(const std::string& name, size_t group, size_t count);
void FilePrepTest(const std::string& name, double percent);

typedef struct {
    int error;
    int correct;
    double average_accuracy;
    double cross_value;
} Parametrs;

}  // namespace study

#endif  // SRC_TYPES_H_
