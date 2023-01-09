#ifndef SRC_MODEL_MATRIX_MODEL_MATRIX_MODEL_H_
#define SRC_MODEL_MATRIX_MODEL_MATRIX_MODEL_H_

#include "../../types.h"
#include "matrix.h"

namespace study {

class MatrixModel {
 public:
    MatrixModel() {
        Init(number_layers_);
        FillRandomWeight();
    }
    ~MatrixModel() {}

    // ОБУЧЕНИЕ
    bool LearnFromFile(std::string name);
    std::string CrossValid(std::string name, size_t group);
    // ТЕСТИРОВАНИЕ
    bool TestFromFile(std::string name);
    // СОХРАНЕНИЕ И ЗАПИСЬ ВЕСОВ
    void SaveWeight(std::string name);
    bool ReadWeight(std::string name);
    void FillRandomWeight();

    void Init(int layer);
    size_t Predict();
    Parametrs GetParametrs();
    void SetIncomes(income_t income);

 private:
    void ActivateFunction(std::vector<double> vector, int size);
    void ActivateMatrix(int layer);
    void ActivateFunctionDerivative();
    void Learn();
    void ForwardFeed();
    void SetInput(std::string line);
    void CountError();
    double ActivateFunctionDerivative(double value);
    void WeightsUpdater(int layer);
    void CalcWeightsDelta(int layer);
    void CalcError(int layer);
    void InitNeuron();

 private:
    int SIZE = 784;
    int SIZE_ALPHABET = 26;
    int neuron_layers = 128;
    double learning_rate_ = 0.1;
    int number_layers_ = 2;  //  кол-во слоев
    std::vector<int> size_neurons_;   //  кол-во нейронов на каждом из слоев
    std::vector<Matrix> weight_;   //  матрица весов
    std::vector<Matrix> neuron_val_;  //  значение нейронов
    std::vector<Matrix> weight_delta_;  //  значение дельта нейронов
    std::vector<Matrix> neuron_err_;   //  значение ошибки для нейронов
    int correct_answer_ = 0;
    std::vector <double> vec_input_;
    Parametrs test_parametr_ = {0, 0, 0.0, 0.0};
};

}  // namespace study

#endif  // SRC_MODEL_MATRIX_MODEL_MATRIX_MODEL_H_
