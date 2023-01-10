#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/matrix_model/matrix_model.h"
#include "../model/graph_model/graph_model.h"
#include "../types.h"

/* Для упрощения переключение между типами прецептронов в контроллере
испоьзуется патерн Стратегия. В объекте контроллера есть указатель на
метринский класс Strategy, в зависимсоти от выбранной стратегии, указатель
начинает выполнять функции одного из дочерних классов - MatrixStrategy или GraphStrategy*/

namespace study {

class Strategy {
 protected:
 public:
    virtual ~Strategy() {}
    virtual void UpdateWigthts() = 0;
    virtual bool LearnFromFile(const std::string& name) = 0;
    virtual bool TestFromFile(const std::string& name) = 0;
    virtual size_t Predict(const income_t& income) = 0;
    virtual void SaveWeights(const std::string& name) = 0;
    virtual Parametrs GetParametrs() = 0;
    virtual std::string CrossValid(const std::string& name, size_t group) = 0;
};

class MatrixStrategy : public Strategy {
 private:
    Controller* ctrl_;
 public:
    explicit MatrixStrategy(Controller *c):ctrl_(c) {}
    void UpdateWigthts() override;
    bool LearnFromFile(const std::string& name) override;
    bool TestFromFile(const std::string& name) override;
    size_t Predict(const income_t& income) override;
    void SaveWeights(const std::string& name) override;
    Parametrs GetParametrs() override;
    std::string CrossValid(const std::string& name, size_t group) override;
};

class GraphStrategy : public Strategy {
 private:
    Controller* ctrl_;
 public:
    explicit GraphStrategy(Controller *c):ctrl_(c) {}
    void UpdateWigthts() override;
    bool LearnFromFile(const std::string& name) override;
    bool TestFromFile(const std::string& name) override;
    size_t Predict(const income_t& income) override;
    void SaveWeights(const std::string& name) override;
    Parametrs GetParametrs() override;
    std::string CrossValid(const std::string& name, size_t group) override;
};

class Controller {
 protected:
    MatrixModel *matrix_;
    GraphPreceptron *graph_;
    MatrixStrategy strat_m;
    GraphStrategy strat_g;
    Strategy* strat_;

 public:
    Controller(MatrixModel *m, GraphPreceptron *g);
    void SetMatrixStrategy();
    void SetGraphStrategy();
    void SetHideSize(size_t size);

    void UpdateWigthts();
    void UpdateWigthtsMatrix();
    void UpdateWigthtsGraph();

    bool LearnFromFile(const std::string& name);
    bool LearnFromFileMatrix(const std::string& name);
    bool LearnFromFileGraph(const std::string& name);

    bool TestFromFile(const std::string& name);
    bool TestFromFileMatrix(const std::string& name);
    bool TestFromFileGraph(const std::string& name);

    size_t Predict(const income_t& income);
    size_t PredictMatrix(const income_t& income);
    size_t PredictGraph(const income_t& income);

    void SaveWeights(const std::string& name);
    void SaveWeightsMatrix(const std::string& name);
    void SaveWeightsGraph(const std::string& name);

    bool LoadWeights(const std::string& name);

    Parametrs GetParametrs();
    Parametrs GetParametrsMatrix();
    Parametrs GetParametrsGraph();

    std::string CrossValid(const std::string& name, size_t group);
    std::string CrossValidMatrix(const std::string& name, size_t group);
    std::string CrossValidGraph(const std::string& name, size_t group);
};

}  // namespace study

#endif  // SRC_CONTROLLER_CONTROLLER_H_

