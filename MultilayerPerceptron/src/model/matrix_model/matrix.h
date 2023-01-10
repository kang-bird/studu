#ifndef SRC_MODEL_MATRIX_MODEL_MATRIX_OOP_H_
#define SRC_MODEL_MATRIX_MODEL_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <ctime>

namespace study {
class Matrix {
 public:
    friend Matrix operator*(const Matrix& other, const double num);
    friend Matrix operator*(const double num, const Matrix& other);

    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    bool eq_matrix(const Matrix& other);
    void sum_matrix(const Matrix& other);
    void sub_matrix(const Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const Matrix& other);
    Matrix transpose();
    Matrix calc_complements();
    double determinant();
    Matrix inverse_matrix();

    void create_matrix(int row, int col);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    bool operator==(const Matrix& other);
    Matrix& operator=(Matrix other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const double num);
    double& operator()(int i, int j);

    int get_rows() const;
    int get_columns() const;
    void set_rows(const int num);
    void set_columns(const int num);
    void set_num(int i, int j, double num);
    void rand();
    void print();

 private:
    int _columns;
    int _rows;
    double** _matrix;

 protected:
    bool equal_size(const Matrix& other);
    Matrix minor_matrix(int column, int row);
    void create_matrix();
};
}  // namespace study

#endif  // SRC_MODEL_MATRIX_MODEL_MATRIX_OOP_H_
