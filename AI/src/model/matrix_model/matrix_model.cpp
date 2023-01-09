#include "matrix_model.h"
#include <algorithm>

namespace study {

void MatrixModel::ActivateMatrix(int layer) {
        for (int j = 0; j < size_neurons_[layer]; j++) {
            neuron_val_[layer].set_num(j, 0, 1 / (1 + pow(M_E, (-neuron_val_[layer](j, 0)))));
        }
}

double MatrixModel::ActivateFunctionDerivative(double value) {
    value = value * (1 - value);
    return value;
}

void MatrixModel::Learn() {
    ForwardFeed();
    CountError();
    CalcWeightsDelta(number_layers_ - 1);
    WeightsUpdater(number_layers_ - 1);
    for (int i = number_layers_-2; i > 0; i--) {
        CalcError(i);
        CalcWeightsDelta(i);
        WeightsUpdater(i);
    }
}

void MatrixModel::CalcError(int layer) {
    neuron_err_[layer] = (weight_[layer].transpose() * weight_delta_[layer+1]);
}
void MatrixModel::CountError() {
    neuron_err_ = neuron_val_;
    weight_delta_ = neuron_val_;
    Matrix matr(SIZE_ALPHABET, 1);
    matr.set_num(correct_answer_, 0, 1);
    neuron_err_[number_layers_-1] = neuron_val_[number_layers_-1] - matr;
}
void MatrixModel::CalcWeightsDelta(int layer) {
    for (int i = 0; i < size_neurons_[layer]; i++) {
        weight_delta_[layer](i, 0) = neuron_err_[layer](i, 0) *
            ActivateFunctionDerivative(neuron_val_[layer](i, 0));
    }
}

void MatrixModel::WeightsUpdater(int layer) {
    Matrix temp(neuron_val_[layer-1] * weight_delta_[layer].transpose());
    weight_[layer-1] -= temp.transpose() * learning_rate_;
}

void MatrixModel::ForwardFeed() {
    InitNeuron();
    for (int i = 1; i < number_layers_; i++) {
        neuron_val_.push_back(weight_[i-1] * neuron_val_[i-1]);
        ActivateMatrix(i);
    }
}

bool MatrixModel::LearnFromFile(std::string name) {
    bool result = false;
    std::ifstream file(name);
    if (!file) {
        result = true;
    } else {
        std::string line;
        while (!file.eof()) {
            std::getline(file, line, ',');
            correct_answer_ = std::atoi(line.c_str()) - 1;
            std::getline(file, line, '\n');
            if (line.size() > 0) {
                SetInput(line);
                Learn();
            }
        }
        file.close();
    }
    return result;
}

void MatrixModel::SetIncomes(income_t income) {
    vec_input_.clear();
    for (int i=0; i < income.size(); i++) {
        vec_input_.push_back(income[i]);
    }
}

size_t MatrixModel::Predict() {
    size_t res = 0;
    if (number_layers_ - 1 == weight_.size()) {
        int i = 1;
        ForwardFeed();
        while (i < size_neurons_[number_layers_-1]) {
            if (neuron_val_[number_layers_-1](i, 0) > neuron_val_[number_layers_-1](res, 0)) {
                res = i;
            }
            i += 1;
        }
    } else {
        std::cerr << "Incorrect number layer. Weights doesn't equel layers" << std::endl;
    }
    return res;
}

bool MatrixModel::TestFromFile(std::string name) {
    bool result = false;
    std::ifstream file(name);
    if (!file) {
        result = true;
    } else {
        size_t error = 0;
        size_t correct = 0;
        double accuracy = 0.0;
        std::string line;
        while (!file.eof()) {
            std::getline(file, line, ',');
            correct_answer_ = std::atoi(line.c_str()) - 1;
            std::getline(file, line, '\n');
            if (line.size() > 0) {
                SetInput(line);
                if (Predict() == correct_answer_) {
                    correct += 1;
                } else {
                    error += 1;
                }
                accuracy += neuron_val_[number_layers_-1](correct_answer_, 0);
            }
        }
        test_parametr_.error = error;
        test_parametr_.correct = correct;
        if ((error != 0) || (correct != 0)) {
            test_parametr_.average_accuracy = accuracy / static_cast<double>(error + correct);
            test_parametr_.cross_value = correct * 100.0 / (error + correct);
        } else {
            test_parametr_.cross_value = 0.0;
            test_parametr_.average_accuracy = 0.0;
        }
        file.close();
    }
    return result;
}

Parametrs MatrixModel::GetParametrs() {
    return test_parametr_;
}

void MatrixModel::SetInput(std::string line) {
    std::istringstream str_number(line);
    std::string str;
    vec_input_.clear();
    while (std::getline(str_number, str, ',')) {
        vec_input_.push_back(std::atol(str.c_str()) / 255.0);
    }
}

void MatrixModel::Init(int layer) {
    size_neurons_.clear();
    number_layers_ = layer + 2;  // Должно подаваться кол-во слоев
    size_neurons_.push_back(SIZE);  // первый слой
    for (int i = 0; i < number_layers_-2; i++) {
        size_neurons_.push_back(neuron_layers);  // все скрытые слои по 128
    }
    size_neurons_.push_back(SIZE_ALPHABET);  // последний слой слой
}

void MatrixModel::FillRandomWeight() {
    srand(time(NULL));
    weight_.clear();
    for (int i = 0; i < number_layers_-1; i++) {
        weight_.push_back(Matrix(size_neurons_[i+1], size_neurons_[i]));
        weight_[i].rand();
    }
}

void MatrixModel::InitNeuron() {
    neuron_val_.clear();
    Matrix matr(SIZE, 1);
    for (int i = 0; i < SIZE; i++) {
        matr.set_num(i, 0, vec_input_[i]);
    }
    neuron_val_.push_back(matr);
}

void MatrixModel::SaveWeight(std::string name) {
    std::ofstream file(name);
    for (int i = 0; i < weight_.size(); i++) {
        for (int k = 0; k < weight_[i].get_rows(); k++) {
            for (int j = 0; j < weight_[i].get_columns(); j++) {
                file << weight_[i](k, j);
                if (j != weight_[i].get_columns() - 1) {
                    file << ",";
                } else {
                    file << std::endl;
                }
            }
        }
    }
    file.close();
}


bool MatrixModel::ReadWeight(std::string name) {
    bool res = true;
    std::ifstream file(name);
    if (!file) {
       std::cout << "NO Setting file!" << std::endl;
    } else {
       weight_.clear();
       std::string line;
       int i = 0, j = 0;
       int flag = 0;
       Matrix weight_input;
       while (!file.eof() && i <number_layers_-1) {
               if (flag == 0) {
                   weight_input.create_matrix(size_neurons_[i+1], size_neurons_[i]);
                   flag++;
               }
               std::getline(file, line, '\n');
               if (line.size() > 0) {
                   int k = 0;
                   std::istringstream str(line);
                   std::string num;
                   while (std::getline(str, num, ',') && k < size_neurons_[i]) {
                       weight_input.set_num(j, k, std::atof(num.c_str()));
                       k++;
                   }
                   j++;
                   if (i < number_layers_-1 && j == size_neurons_[i+1]) {
                       weight_.push_back(weight_input);
                       i++;
                       flag = 0;
                       j = 0;
                   }
               }
       }
       if (weight_.size() != size_neurons_.size() - 1)  {
           std::cerr << "Incorrect number layer" << std::endl;
           res = false;
       }
       file.close();
    }
    return res;
}


std::string MatrixModel::CrossValid(std::string name, size_t group) {
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
    system(("rm " + static_cast<std::string>(kNameLearn)).c_str());
    system(("rm " + static_cast<std::string>(kNameTest)).c_str());
    return result;
}
}  // namespace study
