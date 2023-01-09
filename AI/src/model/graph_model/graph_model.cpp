#include "graph_model.h"

namespace study {

/* --БЛОК ФУНКЦИЙ НЕЙРОНА-- */
// линковка с предыдущими нейронами
void GraphNeuron::SetLinkPrev(GraphNeuron* prev) {
    prev_links_.push_back(prev);
}
// линковка со следующими нейронами
void GraphNeuron::SetLinkNext(GraphNeuron* next) {
    next_links_.push_back(next);
}
// добавление веса
void GraphNeuron::AddWeight(double src) {
    weights_.push_back(src);
}
// установка значения нейрона
void GraphNeuron::SetValue(double src) {
    value_ = src;
}
// установка ошибки нейрона
void GraphNeuron::SetError(double src) {
    error_ = src;
}
// получение значения нейрона
double GraphNeuron::GetValue() {
    return value_;
}
// подсчёт значения нейрона
void GraphNeuron::CalcValue() {
    size_t x = 0;
    value_ = 0;
    while (x < weights_.size()) {
        value_ += weights_[x] * (prev_links_[x])->GetValue();
        x += 1;
    }
    value_ = 1.0 / (1.0 + pow(M_E, -value_));
}
// подсчёт дельты весов
void GraphNeuron::CalcWeightsDelta() {
    weights_delta_ = error_ * value_ * (1 - value_);
}
// перерасчёт новых весов
void GraphNeuron::CalcNewWeights() {
    size_t x = 0;
    while (x < weights_.size()) {
        weights_[x] = weights_[x] - prev_links_[x]->value_ * weights_delta_ * kLearningRate;
        x += 1;
    }
}
// подсчёт ошибки
void GraphNeuron::CalcError(size_t num) {
    size_t x = 0;
    error_ = 0;
    while (x < next_links_.size()) {
        error_ += next_links_[x]->weights_[num] * next_links_[x]->weights_delta_;
        x += 1;
    }
}
// сохранение весов в файл
void GraphNeuron::SaveWeights(std::ofstream* file) {
    size_t x = 0;
    while (x < weights_.size() - 1) {
        *file << weights_[x] << ',';
        x += 1;
    }
    *file << weights_[x] << '\n';  // последний с переносом строки
}
// загрузка весов из файла
void GraphNeuron::LoadWeights(const std::string& src) {
    std::istringstream s(src);
    size_t x = 0;
    std::string line;
    while (x < weights_.size() && std::getline(s, line, ',')) {
        weights_[x] = std::stod(line);
        x += 1;
    }
}
/* ----------------------------------------------- */

/* --БЛОК ФУНКЦИЙ СЛОЯ-- */

// инициализация слоя
void GraphLayer::Init(size_t size) {
    neurons_.clear();
    neurons_.resize(size);
}
// генерируем случайные веса
void GraphLayer::WeightGen(size_t size) {
    size_t x = 0;
    while (x < neurons_.size()) {
        size_t y = 0;
        while (y < size) {
            neurons_[x].AddWeight(0.001 * (std::rand() % 2001 - 1000));
            y += 1;
        }
        x += 1;
    }
}
// линковка с соседними слоями
void GraphLayer::SetLinks(GraphLayer* prev, GraphLayer* next) {
    // если есть предыдущий слой, линкуем нейроны между собой
    if (prev != nullptr) {
        size_t x = 0;
        while (x < prev->neurons_.size()) {
            size_t y = 0;
            while (y < neurons_.size()) {
                neurons_[y].SetLinkPrev(&(prev->neurons_[x]));
                y += 1;
            }
            x += 1;
        }
    }
    // если есть следующий слой, линкуем нейроны между собой
    if (next != nullptr) {
        size_t x = 0;
        while (x < next->neurons_.size()) {
            size_t y = 0;
            while (y < neurons_.size()) {
                neurons_[y].SetLinkNext(&((next->neurons_)[x]));
                y += 1;
            }
            x += 1;
        }
    }
}
// установка значений нейронов слоя
void GraphLayer::SetValues(const income_t& income) {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].SetValue(income[x]);
        x += 1;
    }
}
// считаем значения
void GraphLayer::CalcValues() {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].CalcValue();
        x += 1;
    }
}
// считаем ошибку относительно результата
void GraphLayer::CalcErrorResult(const result_t& result) {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].SetError(neurons_[x].value_ - result[x]);
        x += 1;
    }
}
// считаем разницу весов
void GraphLayer::CalcWeightsDeltas() {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].CalcWeightsDelta();
        x += 1;
    }
}
// перерасчёт весов слоя
void GraphLayer::CalcNewWeights() {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].CalcNewWeights();
        x += 1;
    }
}
// расчёт ошибок слоя
void GraphLayer::CalcErrors() {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].CalcError(x);
        x += 1;
    }
}
// сохранение весов в файл
void GraphLayer::SaveWeights(std::ofstream* file) {
    size_t x = 0;
    while (x < neurons_.size()) {
        neurons_[x].SaveWeights(file);
        x += 1;
    }
}
// загрузка весов из файла
void GraphLayer::LoadWeights(std::ifstream* file) {
    size_t x = 0;
    std::string line;
    while (x < neurons_.size() && std::getline(*file, line, '\n')) {
        neurons_[x].LoadWeights(line);
        x += 1;
    }
}

/* ----------------------------------------------- */

/* --БЛОК ФУНКЦИЙ ПРЕЦЕПТРОНА-- */
// конструктор
GraphPreceptron::GraphPreceptron() {
    Init();
}
// инициализируем и линкуем слои, генерируем веса
void GraphPreceptron::Init() {
    h_layers_.clear();
    // инициализируем слои
    in_layer_.Init(kNeuronInValue);
    size_t x = 0;
    while (x < size_) {
        GraphLayer temp;
        temp.Init(kNeuronHValue);
        h_layers_.push_back(temp);
        x += 1;
    }
    out_layer_.Init(kNeuronOutValue);

    // линкуем слои
    in_layer_.SetLinks(nullptr, &(h_layers_[0]));

    h_layers_[0].SetLinks(&in_layer_, &(h_layers_[1]));
    x = 1;
    while (x < size_ - 1) {
        h_layers_[x].SetLinks(&(h_layers_[x - 1]), &(h_layers_[x + 1]));
        x += 1;
    }
    (h_layers_.back()).SetLinks(&(*(h_layers_.end() - 2)), &out_layer_);
    out_layer_.SetLinks(&(h_layers_.back()), nullptr);

    // генерируем веса
    srand(time(NULL));
    h_layers_[0].WeightGen(kNeuronInValue);
    x = 1;
    while (x < size_) {
        h_layers_[x].WeightGen(kNeuronHValue);
        x += 1;
    }
    out_layer_.WeightGen(kNeuronHValue);
}
// установка кол-ва скрытых весов
void GraphPreceptron::SetHideSize(size_t size) {
    size_ = size;
}
// установка входных значений для первого слоя
void GraphPreceptron::SetIncomes(income_t income) {
    in_layer_.SetValues(income);
}
// расчёт значений для всего прецептрона
void GraphPreceptron::CalcValues() {
    size_t x = 0;
    while (x < size_) {
        h_layers_[x].CalcValues();
        x += 1;
    }
    out_layer_.CalcValues();
}
// указываем, какой элемент должен быть правильный
void GraphPreceptron::ResultInit(size_t num) {
    result_.fill(0);
    result_[num] = 1;
}
// 1 эпоха обучения
void GraphPreceptron::Learn() {
    out_layer_.CalcErrorResult(result_);  // считаем ошибку относительно результата
    out_layer_.CalcWeightsDeltas();  // считаем дельту весов
    out_layer_.CalcNewWeights();  // считаем новые веса
    size_t x = h_layers_.size() - 1;  // запускаем цикл для скрытых слоёв
    while (x < h_layers_.size()) {
        h_layers_[x].CalcErrors();
        h_layers_[x].CalcWeightsDeltas();
        h_layers_[x].CalcNewWeights();
        x -= 1;
    }
}
// парсинг строги для подготовки входных данных
income_t GraphPreceptron::StringPars(std::string src) {
    income_t result;
    std::istringstream s(src);
    size_t x = 0;
    std::string line;
    while (x < kNeuronInValue && std::getline(s, line, ',')) {
        result[x] = std::stol(line) / 255.0;
        x += 1;
    }
    return result;
}
// обучение из файла
bool GraphPreceptron::LearnFromFile(std::string name) {
    bool result = true;
    std::ifstream file(name);
    if (!file) {
        result = false;
    } else {
        std::string line;
        while (!file.eof()) {
            size_t result_num = 0;
            std::getline(file, line, ',');  // считываем номер элемента
            result_num = std::atoi(line.c_str()) - 1;
            std::getline(file, line, '\n');
            if (line.size() > 0) {  // передаём строку на обработку
                SetIncomes(StringPars(line));
                CalcValues();
                ResultInit(result_num);
                Learn();
            }
        }
    }
    return result;
}
// предсказываем
size_t GraphPreceptron::Predict() {
    size_t result = 0;
    CalcValues();
    size_t x = 1;
    while (x < kNeuronOutValue) {
        if (out_layer_.neurons_[x].GetValue() > out_layer_.neurons_[result].GetValue())
            result = x;
        x += 1;
    }
    return result;
}
// тестирование из файла
bool GraphPreceptron::TestFromFile(std::string name) {
    bool result = true;
    std::ifstream file(name);
    if (!file) {
        result = false;
    } else {
        std::string line;
        double accuracy = 0.0;
        size_t cal = 0;
        size_t cal2 = 0;
        while (!file.eof()) {
            size_t element = 0;
            std::getline(file, line, ',');
            element = std::atoi(line.c_str()) - 1;
            std::getline(file, line, '\n');
            if (line.size() > 0) {
                SetIncomes(StringPars(line));
                if (Predict() == element) {
                    cal += 1;
                }
                cal2 += 1;
                accuracy += out_layer_.neurons_[element].GetValue();
            }
        }
        test_parametr_.error = cal2 - cal;
        test_parametr_.correct = cal;
        if (cal2 != 0) {
            test_parametr_.average_accuracy = accuracy / cal2;
            test_parametr_.cross_value = cal * 100.0 / cal2;
        } else {
            test_parametr_.average_accuracy = 0.0;
            test_parametr_.cross_value = 0.0;
        }
    }
    return result;
}
// сохранение весов в файл
void GraphPreceptron::SaveWeights(std::string name) {
    std::ofstream file(name);
        size_t x = 0;
        while (x < size_) {
            h_layers_[x].SaveWeights(&file);
            x += 1;
    }
    out_layer_.SaveWeights(&file);
    if (file)
        file.close();
}
// загрузка весов из файла
bool GraphPreceptron::LoadWeights(std::string name) {
    bool result = false;
    std::ifstream file(name);
    if (file) {
        result = true;
        size_t x = 0;
        while (x < size_) {
            h_layers_[x].LoadWeights(&file);
            x += 1;
        }
        out_layer_.LoadWeights(&file);
        file.close();
    }
    return result;
}
// кроссвалидация
std::string GraphPreceptron::CrossValid(std::string name, size_t group) {
    std::string result = "";
    size_t x = group;
    while (x > 0) {
        study::FilePrep(name, group, x);
        LearnFromFile(kNameLearn);
        TestFromFile(kNameTest);
        std::string temp = std::to_string(test_parametr_.cross_value);
        result += std::to_string(group - x + 1) + ": " + temp.substr(0, temp.find(".") + 3) + "% ";
        x -= 1;
    }
    // удаляем временные файлы
    system(("rm " + static_cast<std::string>(kNameLearn)).c_str());
    system(("rm " + static_cast<std::string>(kNameTest)).c_str());
    return result;
}
// получение струтуры с результатами тестирования
Parametrs GraphPreceptron::GetParametrs() {
    return test_parametr_;
}

/* ----------------------------------------------- */

}  // namespace study
