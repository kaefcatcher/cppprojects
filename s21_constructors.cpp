#include "s21_exceptions.h"
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw IndexOutOfBoundsException();
  }
  matrix_ = new double[rows_ * cols_];
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i * cols_ + j] = 0.0;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_]();
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_]();
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
  other.~S21Matrix();
}

S21Matrix::~S21Matrix() {
  if (this->matrix_) delete[] matrix_;
  this->matrix_ = nullptr;
  this->rows_ = 0;
  this->cols_ = 0;
}