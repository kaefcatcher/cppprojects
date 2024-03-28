#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cstring>
#include <iostream>

#define EPS_DET 1e-100

class S21Matrix {
 private:
  double* matrix_;
  int rows_;
  int cols_;

 public:
  int get_matrix_rows() const;
  int get_matrix_cols() const;
  double get_matrix_element(int row, int col) const;

  void mutate_number_of_cols(int cols);
  void mutate_number_of_rows(int rows);
  void mutate_matrix_element(int row, int col, double val);

  S21Matrix();                        // default constructor
  S21Matrix(int rows, int cols);      // parameterized constructor
  S21Matrix(const S21Matrix& other);  // copy constructor
  S21Matrix(S21Matrix&& other);       // move constructor
  ~S21Matrix();                       // destructor

  // some operators overloads
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double number);
  bool operator==(const S21Matrix& other);
  void operator=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double number);
  double operator()(int i, int j);
  // some public methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};
double calculate_matrix_mul_element(const S21Matrix& matrix1,
                                    const S21Matrix& matrix2, int row, int col);
#endif
