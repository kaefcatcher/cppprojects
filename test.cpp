#include <gtest/gtest.h>

#include "s21_exceptions.h"
#include "s21_matrix_oop.h"
#include "stdio.h"

#define EPS 1e-7

void generate_elements(S21Matrix& matrix);

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

void generate_elements(S21Matrix& matrix) {
  double new_element = 1;
  for (int row = 1; row <= matrix.get_matrix_rows(); row++) {
    for (int col = 1; col <= matrix.get_matrix_cols(); col++) {
      matrix.mutate_matrix_element(row, col, new_element);
      new_element++;
    }
  }
}

TEST(constructor, standart_constructor) {
  S21Matrix matrix;
  EXPECT_EQ(3, matrix.get_matrix_rows());
  EXPECT_EQ(3, matrix.get_matrix_cols());
  EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(1, 1));
}

TEST(constructor, parametric_constructor) {
  S21Matrix matrix{1, 2};
  EXPECT_EQ(1, matrix.get_matrix_rows());
  EXPECT_EQ(2, matrix.get_matrix_cols());
  EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(1, 1));
}

TEST(constructor, constructor_error_negative_rows_cols) {
  try {
    S21Matrix matrix{-1, 2};
    FAIL();
  } catch (const IndexOutOfBoundsException& error) {
    EXPECT_STREQ(error.what(), "Error: Index is out of bounds.");
  }

  try {
    S21Matrix matrix{1, -2};
    FAIL();
  } catch (const IndexOutOfBoundsException& error) {
    EXPECT_STREQ(error.what(), "Error: Index is out of bounds.");
  }

  try {
    S21Matrix matrix{-1, -2};
    FAIL();
  } catch (const IndexOutOfBoundsException& error) {
    EXPECT_STREQ(error.what(), "Error: Index is out of bounds.");
  }
}

TEST(constructor, constructor_copy) {
  S21Matrix matrix{11, 14};
  generate_elements(matrix);
  S21Matrix matrix2(matrix);
  EXPECT_EQ(11, matrix2.get_matrix_rows());
  EXPECT_EQ(14, matrix2.get_matrix_cols());
  EXPECT_DOUBLE_EQ(154, matrix2.get_matrix_element(11, 14));
}

TEST(constructor, constructor_cut) {
  S21Matrix* matrix = new S21Matrix{5, 4};
  generate_elements(*matrix);
  S21Matrix matrix2(std::move(*matrix));
  EXPECT_EQ(5, matrix2.get_matrix_rows());
  EXPECT_EQ(4, matrix2.get_matrix_cols());
  EXPECT_EQ(0, matrix->get_matrix_rows());
  EXPECT_EQ(0, matrix->get_matrix_cols());
  delete matrix;
}

TEST(size_getters, size_getters_work) {
  S21Matrix matrix{1, 1};
  EXPECT_EQ(1, matrix.get_matrix_rows());
  EXPECT_EQ(1, matrix.get_matrix_cols());
}

TEST(element_getter, element_getter_work) {
  S21Matrix matrix{1, 1};
  // EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(0, 0));
  EXPECT_THROW(matrix.get_matrix_element(10, 10), IndexOutOfBoundsException);
  EXPECT_THROW(matrix.get_matrix_element(-10, -10), IndexOutOfBoundsException);
  EXPECT_THROW(matrix.get_matrix_element(-10, 10), IndexOutOfBoundsException);
}

TEST(element_mutator, element_mutator_work) {
  S21Matrix matrix;
  matrix.mutate_matrix_element(1, 1, 1);
  EXPECT_DOUBLE_EQ(1, matrix.get_matrix_element(1, 1));
  EXPECT_THROW(matrix.mutate_matrix_element(10, 10, 1),
               IndexOutOfBoundsException);
}

TEST(sum_matrix, sum_matrix_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  generate_elements(matrix1);
  generate_elements(matrix2);
  matrix1.SumMatrix(matrix2);
  EXPECT_DOUBLE_EQ(2, matrix1.get_matrix_element(1, 1));
  S21Matrix matrix3{2, 3};
  EXPECT_THROW(matrix1.SumMatrix(matrix3), DimensionMismatchException);
}

TEST(sub_matrix, sub_matrix_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  generate_elements(matrix1);
  generate_elements(matrix2);
  matrix1.SubMatrix(matrix2);
  EXPECT_DOUBLE_EQ(0, matrix1.get_matrix_element(2, 2));
  S21Matrix matrix3{2, 3};
  EXPECT_THROW(matrix1.SubMatrix(matrix3), DimensionMismatchException);
}

TEST(mul_number, mul_number_work) {
  S21Matrix matrix1;
  generate_elements(matrix1);
  matrix1.MulNumber(2);
  EXPECT_DOUBLE_EQ(2, matrix1.get_matrix_element(1, 1));
  EXPECT_DOUBLE_EQ(18, matrix1.get_matrix_element(3, 3));
}

TEST(eq_matrix, eq_matrix_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  matrix1.mutate_matrix_element(1, 1, 1);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2.mutate_matrix_element(1, 1, 1);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  matrix2.mutate_matrix_element(3, 3, 1);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  S21Matrix matrix3{2, 3};
  EXPECT_FALSE(matrix1.EqMatrix(matrix3));
}

TEST(cols_mutator, cols_increase) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_number_of_cols(4);
  EXPECT_EQ(4, matrix.get_matrix_cols());
  matrix.mutate_number_of_cols(7);
  EXPECT_EQ(7, matrix.get_matrix_cols());
  matrix.mutate_number_of_cols(8);
  EXPECT_EQ(8, matrix.get_matrix_cols());
  EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(1, 8));
  EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(1, 4));
  EXPECT_DOUBLE_EQ(1, matrix.get_matrix_element(1, 1));
  EXPECT_DOUBLE_EQ(2, matrix.get_matrix_element(1, 2));
  EXPECT_DOUBLE_EQ(3, matrix.get_matrix_element(1, 3));
  EXPECT_DOUBLE_EQ(4, matrix.get_matrix_element(2, 1));
  EXPECT_DOUBLE_EQ(6, matrix.get_matrix_element(2, 3));
  EXPECT_DOUBLE_EQ(7, matrix.get_matrix_element(3, 1));
}

TEST(cols_mutator, cols_decrease) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_number_of_cols(2);
  EXPECT_EQ(2, matrix.get_matrix_cols());
  matrix.mutate_number_of_cols(1);
  EXPECT_EQ(1, matrix.get_matrix_cols());
  EXPECT_DOUBLE_EQ(1, matrix.get_matrix_element(1, 1));
  EXPECT_DOUBLE_EQ(4, matrix.get_matrix_element(2, 1));
  EXPECT_DOUBLE_EQ(7, matrix.get_matrix_element(3, 1));
  EXPECT_THROW(matrix.mutate_number_of_cols(0), IndexOutOfBoundsException);
  EXPECT_THROW(matrix.mutate_number_of_cols(0), IndexOutOfBoundsException);
}

TEST(rows_mutator, rows_increase) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_number_of_rows(4);
  EXPECT_EQ(4, matrix.get_matrix_rows());
  matrix.mutate_number_of_rows(7);
  EXPECT_EQ(7, matrix.get_matrix_rows());
  matrix.mutate_number_of_rows(8);
  EXPECT_EQ(8, matrix.get_matrix_rows());
  EXPECT_DOUBLE_EQ(1, matrix.get_matrix_element(1, 1));
  EXPECT_DOUBLE_EQ(2, matrix.get_matrix_element(1, 2));
  EXPECT_DOUBLE_EQ(3, matrix.get_matrix_element(1, 3));
  EXPECT_DOUBLE_EQ(4, matrix.get_matrix_element(2, 1));
  EXPECT_DOUBLE_EQ(6, matrix.get_matrix_element(2, 3));
  EXPECT_DOUBLE_EQ(7, matrix.get_matrix_element(3, 1));
  // EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(8, 2));
  EXPECT_DOUBLE_EQ(0, matrix.get_matrix_element(7, 2));
}

TEST(rows_mutator, rows_decrease) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_number_of_rows(2);
  EXPECT_EQ(2, matrix.get_matrix_rows());
  matrix.mutate_number_of_rows(1);
  EXPECT_EQ(1, matrix.get_matrix_rows());
  EXPECT_DOUBLE_EQ(1, matrix.get_matrix_element(1, 1));
  EXPECT_DOUBLE_EQ(2, matrix.get_matrix_element(1, 2));
  EXPECT_DOUBLE_EQ(3, matrix.get_matrix_element(1, 3));
  EXPECT_THROW(matrix.mutate_number_of_rows(0), IndexOutOfBoundsException);
  EXPECT_THROW(matrix.mutate_number_of_rows(-10), IndexOutOfBoundsException);
}

TEST(mul_matrix, mul_matrix_work) {
  S21Matrix matrix1{4, 3};
  S21Matrix matrix2{3, 10};
  generate_elements(matrix1);
  generate_elements(matrix2);
  matrix1.MulMatrix(matrix2);
  EXPECT_EQ(4, matrix1.get_matrix_rows());
  EXPECT_EQ(10, matrix1.get_matrix_cols());
  EXPECT_DOUBLE_EQ(680, matrix1.get_matrix_element(4, 10));
  EXPECT_DOUBLE_EQ(383, matrix1.get_matrix_element(4, 1));
  EXPECT_DOUBLE_EQ(380, matrix1.get_matrix_element(3, 5));
  EXPECT_THROW(matrix1.MulMatrix(matrix2), ColumnRowMismatchException);
}

TEST(matrix_transpose, metrix_transpose_work) {
  S21Matrix matrix{3, 2};
  generate_elements(matrix);
  S21Matrix matrix2 = matrix.Transpose();
  EXPECT_EQ(2, matrix2.get_matrix_rows());
  EXPECT_EQ(3, matrix2.get_matrix_cols());
  EXPECT_DOUBLE_EQ(6, matrix2.get_matrix_element(2, 3));
  EXPECT_DOUBLE_EQ(3, matrix2.get_matrix_element(1, 2));
  EXPECT_DOUBLE_EQ(2, matrix2.get_matrix_element(2, 1));
}

TEST(transpose, transpose_work) {
  S21Matrix matrix;
  generate_elements(matrix);
  S21Matrix transpose_matrix = matrix.Transpose();
}

TEST(determinant, determinant_work) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_matrix_element(3, 3, 1);
  EXPECT_DOUBLE_EQ(24, matrix.Determinant());
  matrix.mutate_matrix_element(2, 3, 10);
  EXPECT_DOUBLE_EQ(48, matrix.Determinant());
  S21Matrix easy_matrix{1, 1};
  easy_matrix.mutate_matrix_element(1, 1, 1.25);
  EXPECT_DOUBLE_EQ(1.25, easy_matrix.Determinant());
  S21Matrix hard_matrix{4, 4};
  hard_matrix.mutate_matrix_element(1, 1, 3);
  hard_matrix.mutate_matrix_element(1, 2, -3);
  hard_matrix.mutate_matrix_element(1, 3, -5);
  hard_matrix.mutate_matrix_element(1, 4, 8);
  hard_matrix.mutate_matrix_element(2, 1, -3);
  hard_matrix.mutate_matrix_element(2, 2, 2);
  hard_matrix.mutate_matrix_element(2, 3, 4);
  hard_matrix.mutate_matrix_element(2, 4, -6);
  hard_matrix.mutate_matrix_element(3, 1, 2);
  hard_matrix.mutate_matrix_element(3, 2, -5);
  hard_matrix.mutate_matrix_element(3, 3, -7);
  hard_matrix.mutate_matrix_element(3, 4, 5);
  hard_matrix.mutate_matrix_element(4, 1, -4);
  hard_matrix.mutate_matrix_element(4, 2, 3);
  hard_matrix.mutate_matrix_element(4, 3, 5);
  hard_matrix.mutate_matrix_element(4, 4, -6);
  EXPECT_DOUBLE_EQ(18, hard_matrix.Determinant());
  S21Matrix hard_matrix2{4, 4};
  hard_matrix2.mutate_matrix_element(1, 1, 1);
  hard_matrix2.mutate_matrix_element(1, 2, 0);
  hard_matrix2.mutate_matrix_element(1, 3, 2);
  hard_matrix2.mutate_matrix_element(1, 4, -1);
  hard_matrix2.mutate_matrix_element(2, 1, 3);
  hard_matrix2.mutate_matrix_element(2, 2, 0);
  hard_matrix2.mutate_matrix_element(2, 3, 0);
  hard_matrix2.mutate_matrix_element(2, 4, 5);
  hard_matrix2.mutate_matrix_element(3, 1, 2);
  hard_matrix2.mutate_matrix_element(3, 2, 1);
  hard_matrix2.mutate_matrix_element(3, 3, 4);
  hard_matrix2.mutate_matrix_element(3, 4, -3);
  hard_matrix2.mutate_matrix_element(4, 1, 1);
  hard_matrix2.mutate_matrix_element(4, 2, 0);
  hard_matrix2.mutate_matrix_element(4, 3, 5);
  hard_matrix2.mutate_matrix_element(4, 4, 0);
  EXPECT_DOUBLE_EQ(30, hard_matrix2.Determinant());
  S21Matrix big_matrix{17, 17};
  generate_elements(big_matrix);
  EXPECT_GE(EPS_DET, abs(big_matrix.Determinant()));
  big_matrix.mutate_matrix_element(4, 4, 1);
  EXPECT_GE(EPS_DET, abs(big_matrix.Determinant()));
  S21Matrix error_matrix{1, 2};
  EXPECT_THROW(error_matrix.Determinant(), NonSquareMatrixException);
}

TEST(calc_compliments, calc_compliments_work) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_matrix_element(3, 3, 10);
  S21Matrix compliments_matrix = matrix.CalcComplements();
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(1, 1) - 2));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(1, 2) - 2));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(1, 3) + 3));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(2, 1) - 4));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(2, 2) + 11));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(2, 3) - 6));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(3, 1) + 3));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(3, 2) - 6));
  EXPECT_GE(EPS, abs(compliments_matrix.get_matrix_element(3, 3) + 3));
  S21Matrix error_matrix{1, 2};
  EXPECT_THROW(error_matrix.CalcComplements(), NonSquareMatrixException);
}

TEST(inverse_matrix, inverse_matrix_work) {
  S21Matrix matrix;
  generate_elements(matrix);
  matrix.mutate_matrix_element(3, 3, 10);
  S21Matrix inverse_matrix = matrix.InverseMatrix();
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(1, 1) + 2. / 3.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(1, 2) + 4. / 3.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(1, 3) - 1.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(2, 1) + 2. / 3.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(2, 2) - 11. / 3.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(2, 3) + 2.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(3, 1) - 1.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(3, 2) + 2.));
  EXPECT_GE(EPS, abs(inverse_matrix.get_matrix_element(3, 3) - 1.));
  generate_elements(matrix);
  EXPECT_THROW(matrix.InverseMatrix(), DeterminantZeroException);
  S21Matrix error_matrix{1, 2};
  EXPECT_THROW(error_matrix.InverseMatrix(), NonSquareMatrixException);
}

TEST(plus_operator, plus_operator_work) {
  S21Matrix matrix1;
  generate_elements(matrix1);
  S21Matrix matrix2;
  generate_elements(matrix2);
  matrix2.mutate_matrix_element(3, 3, 100);
  S21Matrix result_matrix = matrix1 + matrix2;
  EXPECT_GE(EPS, abs(result_matrix.get_matrix_element(3, 3) - 109.));
  S21Matrix error_matrix{1, 1};
  EXPECT_THROW(matrix1 + error_matrix, DimensionMismatchException);
}

TEST(minus_operator, minus_operator_work) {
  S21Matrix matrix1;
  generate_elements(matrix1);
  S21Matrix matrix2;
  generate_elements(matrix2);
  matrix2.mutate_matrix_element(3, 3, 100);
  S21Matrix result_matrix = matrix1 - matrix2;
  EXPECT_GE(EPS, abs(result_matrix.get_matrix_element(3, 3) + 91.));
  S21Matrix error_matrix{1, 1};
  EXPECT_THROW(matrix1 - error_matrix, DimensionMismatchException);
}

TEST(mul_matrix_operator, mul_matrix_operator_work) {
  S21Matrix matrix1{4, 3};
  S21Matrix matrix2{3, 10};
  generate_elements(matrix1);
  generate_elements(matrix2);
  S21Matrix result_matrix = matrix1 * matrix2;
  EXPECT_EQ(4, result_matrix.get_matrix_rows());
  EXPECT_EQ(10, result_matrix.get_matrix_cols());
  EXPECT_DOUBLE_EQ(680, result_matrix.get_matrix_element(4, 10));
  EXPECT_DOUBLE_EQ(383, result_matrix.get_matrix_element(4, 1));
  EXPECT_DOUBLE_EQ(380, result_matrix.get_matrix_element(3, 5));
  EXPECT_THROW(result_matrix * matrix2, ColumnRowMismatchException);
}

TEST(mul_number_operator, mul_number_operator_work) {
  S21Matrix matrix1;
  generate_elements(matrix1);
  S21Matrix result_matrix = matrix1 * 2;
  EXPECT_DOUBLE_EQ(2, result_matrix.get_matrix_element(1, 1));
  EXPECT_DOUBLE_EQ(18, result_matrix.get_matrix_element(3, 3));
}

TEST(eq_matrix_operator, eq_matrix_operator_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  EXPECT_TRUE(matrix1 == matrix2);
  matrix1.mutate_matrix_element(1, 1, 1);
  EXPECT_FALSE(matrix1 == matrix2);
  matrix2.mutate_matrix_element(1, 1, 1);
  EXPECT_TRUE(matrix1 == matrix2);
  matrix2.mutate_matrix_element(3, 3, 1);
  EXPECT_FALSE(matrix1 == matrix2);
  S21Matrix matrix3{2, 3};
  EXPECT_FALSE(matrix1 == matrix3);
}

TEST(new_eq_matrix_operator, new_eq_matrix_operator_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  generate_elements(matrix1);
  matrix2 = matrix1;
  EXPECT_GE(EPS, abs(matrix2.get_matrix_element(3, 3) - 9.));
}

TEST(sum_eq_operator, sum_eq_operator_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  generate_elements(matrix1);
  generate_elements(matrix2);
  matrix1 += matrix2;
  EXPECT_GE(EPS, abs(matrix1.get_matrix_element(3, 3) - 18.));
  S21Matrix matrix3{2, 3};
  EXPECT_THROW(matrix1 += matrix3, DimensionMismatchException);
}

TEST(minus_eq_operator, minus_eq_operator_work) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  generate_elements(matrix1);
  generate_elements(matrix2);
  matrix1 -= matrix2;
  EXPECT_GE(EPS, abs(matrix1.get_matrix_element(3, 3)));
  S21Matrix matrix3{2, 3};
  EXPECT_THROW(matrix1 -= matrix3, DimensionMismatchException);
}

TEST(mul_number_eq_operator, mul_number_eq_operator_work) {
  S21Matrix matrix1;
  generate_elements(matrix1);
  matrix1 *= 2;
  EXPECT_GE(EPS, abs(matrix1.get_matrix_element(1, 1) - 2));
  EXPECT_GE(EPS, abs(matrix1.get_matrix_element(3, 3) - 18));
}

TEST(mul_matrix_eq_operator, mul_matrix_eq_operator_work) {
  S21Matrix matrix1{4, 3};
  S21Matrix matrix2{3, 10};
  generate_elements(matrix1);
  generate_elements(matrix2);
  matrix1 *= matrix2;
  EXPECT_EQ(4, matrix1.get_matrix_rows());
  EXPECT_EQ(10, matrix1.get_matrix_cols());
  EXPECT_DOUBLE_EQ(680, matrix1.get_matrix_element(4, 10));
  EXPECT_DOUBLE_EQ(383, matrix1.get_matrix_element(4, 1));
  EXPECT_DOUBLE_EQ(380, matrix1.get_matrix_element(3, 5));
  EXPECT_THROW(matrix1 *= matrix2, ColumnRowMismatchException);
}

TEST(index_operator, index_operator_work) {
  S21Matrix matrix;
  generate_elements(matrix);
  EXPECT_GE(EPS, abs(matrix(3, 3) - 9.));
  EXPECT_GE(EPS, abs(matrix(2, 2) - 5.));
}
