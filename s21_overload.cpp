#include "s21_exceptions.h"
#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double scalar) {
  S21Matrix result(*this);
  result.MulNumber(scalar);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

void S21Matrix::operator=(const S21Matrix& other) {
  this->~S21Matrix();
  rows_ = other.get_matrix_rows();
  cols_ = other.get_matrix_cols();
  this->matrix_ = new double[rows_ * cols_]();
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}

void S21Matrix::operator+=(const S21Matrix& other) { this->SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { this->SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { this->MulMatrix(other); }

void S21Matrix::operator*=(const double number) { this->MulNumber(number); }

double S21Matrix::operator()(int i, int j) {
  return this->get_matrix_element(i, j);
}
