#include "s21_exceptions.h"
#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool status = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    status = false;
  else {
    for (int element = 0; element < this->rows_ * this->cols_; element++) {
      if (this->matrix_[element] != other.matrix_[element]) status = false;
    }
  }
  return status;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw DimensionMismatchException();
  }
  for (int element = 0; element < this->rows_ * this->cols_; element++) {
    this->matrix_[element] = this->matrix_[element] + other.matrix_[element];
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw DimensionMismatchException();
  }
  for (int element = 0; element < this->rows_ * this->cols_; element++) {
    this->matrix_[element] = this->matrix_[element] - other.matrix_[element];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int element = 0; element < this->rows_ * this->cols_; element++) {
    this->matrix_[element] = this->matrix_[element] * num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw ColumnRowMismatchException();
  }
  double *mul_result_matrix = new double[this->rows_ * other.cols_];
  for (int row = 1; row <= this->rows_; row++) {
    for (int col = 1; col <= other.cols_; col++) {
      mul_result_matrix[other.cols_ * (row - 1) + col - 1] =
          calculate_matrix_mul_element(*this, other, row, col);
    }
  }
  delete[] this->matrix_;
  this->matrix_ = mul_result_matrix;
  this->cols_ = other.cols_;
}

double calculate_matrix_mul_element(const S21Matrix &matrix1,
                                    const S21Matrix &matrix2, int row,
                                    int col) {
  double result = 0;
  for (int term = 1; term <= matrix1.get_matrix_cols(); term++) {
    result += matrix1.get_matrix_element(row, term) *
              matrix2.get_matrix_element(term, col);
  }
  return result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result_matrix{this->cols_, this->rows_};
  for (int row = 1; row <= this->rows_; row++) {
    for (int col = 1; col <= this->cols_; col++) {
      result_matrix.matrix_[this->rows_ * (col - 1) + row - 1] =
          this->get_matrix_element(row, col);
    }
  }
  return result_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw NonSquareMatrixException();

  S21Matrix complements(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix submatrix(rows_ - 1, cols_ - 1);
      int sub_i = 0, sub_j = 0;
      for (int row = 0; row < rows_; ++row) {
        if (row == i) continue;
        for (int col = 0; col < cols_; ++col) {
          if (col == j) continue;
          submatrix.matrix_[sub_i * (cols_ - 1) + sub_j] =
              matrix_[row * cols_ + col];
          ++sub_j;
        }
        ++sub_i;
        sub_j = 0;
      }
      double det = submatrix.Determinant();
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      complements.matrix_[i * cols_ + j] = sign * det;
    }
  }

  return complements;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw NonSquareMatrixException();

  if (rows_ == 1) {
    return matrix_[0];
  } else if (rows_ == 2) {
    return matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
  } else {
    double det = 1.0;
    S21Matrix temp = *this;
    for (int i = 0; i < rows_ - 1; ++i) {
      int max_row = i;
      for (int j = i + 1; j < rows_; ++j) {
        if (std::abs(temp.matrix_[j * cols_ + i]) >
            std::abs(temp.matrix_[max_row * cols_ + i])) {
          max_row = j;
        }
      }
      if (max_row != i) {
        for (int k = 0; k < cols_; ++k) {
          std::swap(temp.matrix_[i * cols_ + k],
                    temp.matrix_[max_row * cols_ + k]);
        }
        det = -det;
      }
      for (int j = i + 1; j < rows_; ++j) {
        double ratio =
            temp.matrix_[j * cols_ + i] / temp.matrix_[i * cols_ + i];
        for (int k = i; k < cols_; ++k) {
          temp.matrix_[j * cols_ + k] -= ratio * temp.matrix_[i * cols_ + k];
        }
      }
    }
    for (int i = 0; i < rows_; ++i) {
      det *= temp.matrix_[i * cols_ + i];
    }

    return det;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();

  if (abs(det) < EPS_DET) throw DeterminantZeroException();

  S21Matrix complements = this->CalcComplements();
  S21Matrix adjugate = complements.Transpose();

  S21Matrix inverse(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      inverse.matrix_[i * cols_ + j] = adjugate.matrix_[i * cols_ + j] / det;
    }
  }

  return inverse;
}
