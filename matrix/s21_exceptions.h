#ifndef S21_EXCEPTIONS_H
#define S21_EXCEPTIONS_H
#include <exception>
#include <string>

class S21Exception : public std::exception {
 public:
  S21Exception(const std::string& message) : message_(message) {}

  virtual ~S21Exception() throw() {}

  virtual const char* what() const throw() { return message_.c_str(); }

 private:
  std::string message_;
};

class DimensionMismatchException : public S21Exception {
 public:
  DimensionMismatchException()
      : S21Exception("Error: Different matrix dimensions.") {}
};

class ColumnRowMismatchException : public S21Exception {
 public:
  ColumnRowMismatchException()
      : S21Exception(
            "Error: Number of columns of the first matrix is not equal to the "
            "number of rows of the second matrix.") {}
};

class NonSquareMatrixException : public S21Exception {
 public:
  NonSquareMatrixException() : S21Exception("Error: Matrix is not square.") {}
};

class DeterminantZeroException : public S21Exception {
 public:
  DeterminantZeroException()
      : S21Exception("Error: Determinant of the matrix is zero.") {}
};

class IndexOutOfBoundsException : public S21Exception {
 public:
  IndexOutOfBoundsException()
      : S21Exception("Error: Index is out of bounds.") {}
};

#endif