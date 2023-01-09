#ifndef SRC_MODEL_GRAPH_MODEL_GRAPH_MODEL_H_
#define SRC_MODEL_GRAPH_MODEL_GRAPH_MODEL_H_

#include "../../types.h"

namespace study {

// класс нейрона
class GraphNeuron {
    friend class GraphLayer;
 private:
    double value_ = 0;  // значение нейрона
    double error_ = 0;  // ошибка нейрона
    double weights_delta_ = 0;  // разница весов нейрона
    std::vector<GraphNeuron*> prev_links_;  // вектор указателей на нейроны предыдущего слоя
    std::vector<GraphNeuron*> next_links_;  // вектор указателей на нейроны следующего слоя
    std::vector<double> weights_;  // вектор весов

 public:
    // мутаторы
    void SetLinkPrev(GraphNeuron* prev);
    void SetLinkNext(GraphNeuron* next);
    void AddWeight(double src);
    void SetValue(double src);
    void SetError(double src);
    // ассессоры
    double GetValue();
    // калькуляция
    void CalcValue();
    void CalcWeightsDelta();
    void CalcNewWeights();
    void CalcError(size_t num);
    // работа с весами
    void SaveWeights(std::ofstream* file);
    void LoadWeights(const std::string& src);
};


// класс слоя
class GraphLayer {
    friend class GraphPreceptron;
 private:
    std::vector<GraphNeuron> neurons_;  // вектор нейронов

 public:
    void Init(size_t size);
    void SetLinks(GraphLayer* prev, GraphLayer* next);
    void SetValues(const income_t& income);
    void WeightGen(size_t size);
    void CalcValues();
    void CalcErrorResult(const result_t& result);
    void CalcWeightsDeltas();
    void CalcNewWeights();
    void CalcErrors();
    void SaveWeights(std::ofstream* file);
    void LoadWeights(std::ifstream* file);
};


// класс прецептрона
class GraphPreceptron {
 private:
    size_t size_ = 2;  // кол-во скрытых слоёв
    GraphLayer in_layer_;  // входной слой
    std::vector<GraphLayer> h_layers_;  // вектор скрытых слоёв
    GraphLayer out_layer_;  // выходной слой
    result_t result_ = { 0 };  // массив результата
    Parametrs test_parametr_ = {0, 0, 0.0, 0.0};  // структура с результатами тестирвоания

    void CalcValues();
    void ResultInit(size_t num);
    void Learn();
    income_t StringPars(std::string src);

 public:
    GraphPreceptron();
    ~GraphPreceptron() {}
    void Init();
    void SetHideSize(size_t size);
    void SetIncomes(income_t income);
    bool LearnFromFile(std::string name);
    size_t Predict();
    bool TestFromFile(std::string name);
    void SaveWeights(std::string name);
    bool LoadWeights(std::string name);
    std::string CrossValid(std::string name, size_t group);
    Parametrs GetParametrs();
};

}  // namespace study

#endif  // SRC_MODEL_GRAPH_MODEL_GRAPH_MODEL_H_
