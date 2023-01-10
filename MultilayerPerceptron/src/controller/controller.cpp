#include "controller.h"

namespace study {

/* --БЛОК ФУНКЦИЙ ПАТТЕРНА СТРАТЕГИЯ-- */

// тестирование из файла
void GraphStrategy::UpdateWigthts() {
    return ctrl_->UpdateWigthtsGraph();
}
void MatrixStrategy::UpdateWigthts() {
    return ctrl_->UpdateWigthtsMatrix();
}

// обучение из файла
bool GraphStrategy::LearnFromFile(const std::string& name) {
    return ctrl_->LearnFromFileGraph(name);
}
bool MatrixStrategy::LearnFromFile(const std::string& name) {
    return ctrl_->LearnFromFileMatrix(name);
}

// тестирование из файла
bool GraphStrategy::TestFromFile(const std::string& name) {
    return ctrl_->TestFromFileGraph(name);
}
bool MatrixStrategy::TestFromFile(const std::string& name) {
    return ctrl_->TestFromFileMatrix(name);
}

// предсказать
size_t GraphStrategy::Predict(const income_t& income) {
    return ctrl_->PredictGraph(income);
}
size_t MatrixStrategy::Predict(const income_t& income) {
    return ctrl_->PredictMatrix(income);
}

// сохранение весов
void GraphStrategy::SaveWeights(const std::string& name)  {
    return ctrl_->SaveWeightsGraph(name);
}
void MatrixStrategy::SaveWeights(const std::string& name)  {
    return ctrl_->SaveWeightsMatrix(name);
}

// получение параметров
Parametrs GraphStrategy::GetParametrs()  {
    return ctrl_->GetParametrsGraph();
}
Parametrs MatrixStrategy::GetParametrs() {
    return ctrl_->GetParametrsMatrix();
}

// кроссвалидация
std::string GraphStrategy::CrossValid(const std::string& name, size_t group)  {
    return ctrl_->CrossValidGraph(name, group);
}
std::string MatrixStrategy::CrossValid(const std::string& name, size_t group) {
    return ctrl_->CrossValidMatrix(name, group);
}

/* ----------------------------------------------- */

/* --БЛОК ФУНКЦИЙ КОНТРОЛЛЕРА-- */
// конструктор
Controller::Controller(MatrixModel *m, GraphPreceptron *g):strat_m(this), strat_g(this) {
    matrix_ = m;
    graph_ = g;
    strat_ = &strat_m;
}


// установка определённой стратегии
void Controller::SetMatrixStrategy() {
    strat_ = &strat_m;
}
void Controller::SetGraphStrategy() {
    strat_ = &strat_g;
}

// задание кол-ва скрытых слоёв
void Controller::SetHideSize(size_t size) {
    if (size <= 5 && size >= 2) {
        matrix_->Init(size);
        matrix_->FillRandomWeight();
        graph_->SetHideSize(size);
        graph_->Init();
    }
}

// сброс весов
void Controller::UpdateWigthts() {
    strat_->UpdateWigthts();
}
void Controller::UpdateWigthtsMatrix() {
    matrix_->FillRandomWeight();
}
void Controller::UpdateWigthtsGraph() {
    graph_->Init();
}

// обучение из файла
bool Controller::LearnFromFile(const std::string& name) {
    return strat_->LearnFromFile(name);
}
bool Controller::LearnFromFileMatrix(const std::string& name) {
    return matrix_->LearnFromFile(name);;
}
bool Controller::LearnFromFileGraph(const std::string& name) {
    return graph_->LearnFromFile(name);
}

// тестирование из файла
bool Controller::TestFromFile(const std::string& name) {
    return strat_->TestFromFile(name);
}
bool Controller::TestFromFileMatrix(const std::string& name) {
    return matrix_->TestFromFile(name);;
}
bool Controller::TestFromFileGraph(const std::string& name) {
    return graph_->TestFromFile(name);;
}

// предсказать
size_t Controller::Predict(const income_t& income) {
    return strat_->Predict(income);
}
size_t Controller::PredictMatrix(const income_t& income) {
    matrix_->SetIncomes(income);
    return matrix_->Predict();
}
size_t Controller::PredictGraph(const income_t& income) {
    graph_->SetIncomes(income);
    return graph_->Predict();
}

// сохранение весов
void Controller::SaveWeights(const std::string& name) {
    strat_->SaveWeights(name);
}
void Controller::SaveWeightsMatrix(const std::string& name) {
    matrix_->SaveWeight(name);
}
void Controller::SaveWeightsGraph(const std::string& name) {
    graph_->SaveWeights(name);
}

// загрузка весов
bool Controller::LoadWeights(const std::string& name) {
    return  matrix_->ReadWeight(name) && graph_->LoadWeights(name);
}

// Получение тестовых параметров
Parametrs Controller::GetParametrs() {
    return strat_->GetParametrs();
}
Parametrs Controller::GetParametrsMatrix() {
    return matrix_->GetParametrs();
}
Parametrs Controller::GetParametrsGraph() {
    return graph_->GetParametrs();
}

// кросс валидация
std::string Controller::CrossValid(const std::string& name, size_t group) {
    return strat_->CrossValid(name, group);
}
std::string Controller::CrossValidMatrix(const std::string& name, size_t group) {
    matrix_->FillRandomWeight();
    return matrix_->CrossValid(name, group);
}
std::string Controller::CrossValidGraph(const std::string& name, size_t group) {
    graph_->Init();
    return graph_->CrossValid(name, group);
}

/* ----------------------------------------------- */

}  // namespace study

