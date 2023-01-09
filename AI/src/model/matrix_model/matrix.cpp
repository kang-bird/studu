#include "matrix.h"

namespace study {
Matrix::Matrix() : _rows(2), _columns(2) {
    create_matrix();
}

Matrix::Matrix(int rows, int cols) : _rows(rows), _columns(cols) {
    if (_rows <= 0 || _columns <= 0) {
        throw std::out_of_range("Error: Index must be positive");
    }
    create_matrix();
}

Matrix::Matrix(const Matrix& other) : _rows(other._rows), _columns(other._columns) {
    create_matrix();
    for (int i = 0; i < _rows; i++) {
        for (int j  = 0; j < _columns; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& other): _rows(0), _columns(0), _matrix(nullptr) {
    std::swap(_rows, other._rows);
    std::swap(_columns, other._columns);
    std::swap(_matrix, other._matrix);
}

Matrix::~Matrix() {
    if (_matrix) {
        for (int i = 0; i < _rows; i++) {
            if (this->_matrix[i] != nullptr) {
                delete[] _matrix[i];
            }
        }
        delete[] _matrix;
    }
}

bool Matrix::eq_matrix(const Matrix& other) {
    bool res = true;
    if (equal_size(other) == true) {
        for (int i = 0; i < _rows && res == true; i++) {
            for (int j = 0; j < _columns && res == true; j++) {
                if (fabs(_matrix[i][j] - other._matrix[i][j]) >= 1e-7) {
                    res = false;
                }
            }
        }
    } else {
        res = false;
    }
    return res;
}

void Matrix::sum_matrix(const Matrix& other) {
    if (equal_size(other) == false) {
        throw std::out_of_range("Error: Matrices have different sizes");
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}

void Matrix::sub_matrix(const Matrix& other) {
    if (equal_size(other) == false) {
        throw std::out_of_range("Error: Matrices have different sizes");
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
}

void Matrix::mul_number(const double num) {
    if (std::isnan(num) || std::isinf(num)) {
        throw std::out_of_range("Error: Numper value is incorrect");
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            _matrix[i][j] *= num;
        }
    }
}

void Matrix::mul_matrix(const Matrix& other) {
    if (_columns != other._rows) {
        throw std::out_of_range("Error: Columns first matrix"
                                 "is ​​not equal rows second matrix");
    }
    Matrix tempMatrix(_rows, other._columns);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            for (int k = 0; k < _columns; k++) {
                tempMatrix._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    this->~Matrix();
    _columns = other._columns;
    create_matrix();
    *this = tempMatrix;
}

Matrix Matrix::transpose() {
    Matrix res(_columns, _rows);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _columns; j++) {
                res._matrix[j][i] = _matrix[i][j];
            }
        }
    return res;
}

Matrix Matrix::calc_complements() {
    if (_rows != _columns) {
        throw std::out_of_range("Error: Matrix must be square");
    }
    Matrix res(_rows, _rows);
    if (this->_rows == 1) {
        res._matrix[0][0] = 1;
    } else {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _rows; j++) {
            Matrix minor = this->minor_matrix(i, j);
            res._matrix[i][j] = pow(-1, i + j) * minor.determinant();
        }
    }
    }
    return res;
}

double Matrix::determinant() {
    if (_rows != _columns) {
        throw std::out_of_range("Error: Matrix must be square");
    }
    double res = 0.0;
    if (_rows == 1) {
        res = _matrix[0][0];
    }
    if (_rows == 2) {
        res = _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
    }
    if (_rows > 2) {
        for (int i = 0; i < _rows; i++) {
            Matrix minor = this->minor_matrix(i, 0);
            res += pow(-1, i) * _matrix[i][0] * minor.determinant();
        }
    }
    return res;
}

Matrix Matrix::inverse_matrix() {
    double determ = this->determinant();
    if (determ == 0) {
        throw std::out_of_range("Error: Matrix determinant is 0");
    }
    Matrix result_complements = this->calc_complements();
    Matrix result = result_complements.transpose();
    result.mul_number(1 / determ);
    return result;
}

Matrix& Matrix::operator=(Matrix other) {
    if (this != &other) {
        _rows = other._rows;
        _columns = other._columns;
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _columns; j++) {
                _matrix[i][j] = other._matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
    Matrix resMatrix(*this);
    resMatrix.sum_matrix(other);
    return resMatrix;
}

Matrix Matrix::operator-(const Matrix& other) {
    Matrix resMatrix(*this);
    resMatrix.sub_matrix(other);
    return resMatrix;
}

Matrix Matrix::operator*(const Matrix& other) {
    Matrix resMatrix(*this);
    resMatrix.mul_matrix(other);
    return resMatrix;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    sum_matrix(other);
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    sub_matrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    mul_matrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}

bool Matrix::operator==(const Matrix& other) {
    return this->eq_matrix(other);
}

double& Matrix::operator()(int i, int j) {
    if (i >= _rows || j >= _columns || i < 0 || j < 0) {
        throw std::out_of_range("Error: Index incorrect");
    }
    return _matrix[i][j];
}


Matrix operator*(const double num, const Matrix& other) {
    Matrix resMatrix(other);
    resMatrix.mul_number(num);
    return resMatrix;
}

Matrix operator*(const Matrix& other, const double num) {
    Matrix resMatrix(other);
    resMatrix.mul_number(num);
    return resMatrix;
}

int Matrix::get_rows() const {
    return _rows;
}
int Matrix::get_columns() const {
    return _columns;
}
void Matrix::set_rows(const int num) {
    _rows = num;
}
void Matrix::set_columns(const int num) {
    _columns = num;
}

void Matrix::set_num(int i, int j, double num) {
    if (i >= _rows || j >= _columns || i < 0 || j < 0) {
        throw std::out_of_range("Error: Index incorrect");
    }
    _matrix[i][j] = num;
}

void Matrix::create_matrix() {
    _matrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new double[_columns];
        for (int j = 0; j < _columns; j++) {
            _matrix[i][j] = 0;
        }
    }
}
void Matrix::create_matrix(int row, int col) {
    _rows = row;
    _columns = col;
    create_matrix();
}

Matrix Matrix::minor_matrix(int column, int row) {
    Matrix res(_rows - 1, _rows - 1);
    int newi = 0;
    for (int i = 0; i < _rows; i++) {
        if (column != i) {
            int newj = 0;
            for (int j = 0; j < _rows; j++) {
                if (row != j) {
                    res._matrix[newi][newj] = _matrix[i][j];
                    newj++;
                }
            }
            newi++;
        }
    }
    return res;
}

bool Matrix::equal_size(const Matrix& other) {
  return _rows == other._rows && _columns == other._columns;
}

void Matrix::print() {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout <<"\n";
    }
}
void Matrix::rand() {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            _matrix[i][j] = 0.001 * (std::rand() % 2001 - 1000);
        }
    }
}

}  // namespace study
