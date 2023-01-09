#include "controller/controller.h"
#include <gtest/gtest.h>

TEST(mlp, graph_base) {
    study::GraphPreceptron graph;
    graph.SetHideSize(4);
    graph.Init();

    graph.LearnFromFile("datasets/tests_train.csv");

    ASSERT_LE(graph.Predict(), 25);
    ASSERT_GT((graph.CrossValid("datasets/tests_train.csv", 5)).size(), 0);
}

TEST(mlp, graph_weights) {
    study::GraphPreceptron graph_1;
    study::GraphPreceptron graph_2;
    graph_1.Init();
    graph_2.Init();

    graph_1.LearnFromFile("datasets/tests_train.csv");
    graph_2.LearnFromFile("datasets/tests_train.csv");

    graph_1.SaveWeights(".temp.csv");
    graph_2.LoadWeights(".temp.csv");
    ASSERT_EQ(graph_1.Predict(), graph_1.Predict());
    system("rm -f .temp.csv");
}

TEST(mlp, matrix_base) {
    study::MatrixModel matrix;
    matrix.Init(3);
    matrix.FillRandomWeight();

    matrix.LearnFromFile("datasets/tests_train.csv");

    ASSERT_LE(matrix.Predict(), 25);
    ASSERT_GT((matrix.CrossValid("datasets/tests_train.csv", 7)).size(), 0);
}

TEST(mlp, matrix_weights) {
    study::MatrixModel matrix_1;
    study::MatrixModel matrix_2;
    matrix_1.Init(5);
    matrix_2.Init(5);
    matrix_1.FillRandomWeight();
    matrix_2.FillRandomWeight();

    matrix_1.LearnFromFile("datasets/tests_train.csv");
    matrix_1.SaveWeight(".temp.csv");
    matrix_2.ReadWeight(".temp.csv");

    study::income_t income = { 0 };
    matrix_1.SetIncomes(income);
    matrix_2.SetIncomes(income);

    ASSERT_EQ(matrix_1.Predict(), matrix_2.Predict());
    system("rm -f .temp.csv");
}

TEST(mlp, controller_graph) {
    study::MatrixModel m;
    study::GraphPreceptron g;
    study::Controller ctrl(&m, &g);
    study::income_t income = { 0 };

    ctrl.SetGraphStrategy();
    ctrl.SetHideSize(3);
    ctrl.UpdateWigthts();
    ctrl.LearnFromFile("datasets/tests_train.csv");
    ctrl.TestFromFile("datasets/tests_train.csv");
    ctrl.Predict(income);
    ctrl.SaveWeights(".temp.csv");
    ctrl.LoadWeights(".temp.csv");
    ctrl.GetParametrs();
    ctrl.CrossValid("datasets/tests_train.csv", 2);
}

TEST(mlp, controller_matrix) {
    study::MatrixModel m;
    study::GraphPreceptron g;
    study::Controller ctrl(&m, &g);
    study::income_t income = { 0 };

    ctrl.SetMatrixStrategy();
    ctrl.SetHideSize(3);
    ctrl.UpdateWigthts();
    ctrl.LearnFromFile("datasets/tests_train.csv");
    ctrl.TestFromFile("datasets/tests_train.csv");
    ctrl.Predict(income);
    ctrl.SaveWeights(".temp.csv");
    ctrl.LoadWeights(".temp.csv");
    ctrl.GetParametrs();
    ctrl.CrossValid("datasets/tests_train.csv", 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
