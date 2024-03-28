#include "s21_exceptions.h"
#include "s21_matrix_oop.h"

int S21Matrix::get_matrix_rows() const { return this->rows_; }

int S21Matrix::get_matrix_cols() const { return this->cols_; }

double S21Matrix::get_matrix_element(int row, int col) const {
  if (row < 1 || col < 1 || row > this->rows_ || col > this->cols_) {
    throw IndexOutOfBoundsException();
  }
  return this->matrix_[(this->cols_ * (row - 1)) + col - 1];
}

void S21Matrix::mutate_matrix_element(int row, int col, double val) {
  if (row < 1 || col < 1 || row > this->rows_ || col > this->cols_) {
    throw IndexOutOfBoundsException();
  }

  this->matrix_[(this->cols_ * (row - 1)) + col - 1] = val;
}

void S21Matrix::mutate_number_of_cols(int new_cols) {
  if (new_cols < 1) {
    throw IndexOutOfBoundsException();
  }
  double *new_matrix = new double[this->rows_ * new_cols];
  for (int row = 0; row < this->rows_; row++) {
    for (int col = 0; col < new_cols; col++) {
      if (col < this->cols_) {
        new_matrix[row * new_cols + col] =
            this->get_matrix_element(row + 1, col + 1);
      } else {
        new_matrix[row * new_cols + col] = 0.0;  // Fill with 0 for new columns
      }
    }
  }
  delete[] this->matrix_;
  this->matrix_ = new_matrix;
  this->cols_ = new_cols;
}

void S21Matrix::mutate_number_of_rows(int new_rows) {
  if (new_rows < 1) {
    throw IndexOutOfBoundsException();
  }
  double *new_matrix = new double[new_rows * this->cols_];
  for (int row = 0; row < new_rows; row++) {
    for (int col = 0; col < this->cols_; col++) {
      if (row < this->rows_) {
        new_matrix[row * this->cols_ + col] =
            this->get_matrix_element(row + 1, col + 1);
      } else {
        new_matrix[row * this->cols_ + col] = 0.0;  // Fill with 0 for new rows
      }
    }
  }
  delete[] this->matrix_;
  this->matrix_ = new_matrix;
  this->rows_ = new_rows;
}
