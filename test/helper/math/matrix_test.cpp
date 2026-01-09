/**
 ******************************************************************************
 * @file    matrix_test.cpp
 * @brief   Unit tests for Matrix class.
 ******************************************************************************
 */

#include "matrix.hpp"

#include <gtest/gtest.h>

#include <complex>

#include "test_helper.h"

typedef std::complex<double> DoubleComplex;

/** @brief Tests matrix dimensions are correct at initialization. */
TEST(Matrix, Dimension) {
  // Initialize a matrix.
  size_t r = 9;
  size_t c = 3;
  Matrix<double> m{r, c};

  // Assert that matrix dimension is as same as initialization.
  ASSERT_EQ(m.getNumRows(), r);
  ASSERT_EQ(m.getNumCols(), c);

  ASSERT_EQ(m.size().first, r);
  ASSERT_EQ(m.size().second, c);
}

/** @brief Tests matrix resizing. */
TEST(Matrix, Resizing) {
  // Initialize a matrix.
  size_t r = 9;
  size_t c = 3;
  Matrix<double> m{r, c};

  // Resize the matrix.
  size_t newR = 4;
  size_t newC = 2;
  std::pair<size_t, size_t> newSize = std::make_pair(newR, newC);
  m.resize(newSize);

  // Assert that matrix resizing changes the matrix dimension.
  ASSERT_EQ(m.getNumRows(), newR);
  ASSERT_EQ(m.getNumCols(), newC);
  ASSERT_EQ(m.size(), newSize);
}

/** @brief Verify that access single cells from the matrix returns the correct
 * value. */
TEST(Matrix, SingleCellAccess) {
  // Initialize the matrix with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Matrix<double> m{r, c, data};

  // Assert accessing data at specific cells is correct.
  double num = 1.0;
  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(m(i, j), num, PRECISION_ERROR);
      num += 1.0;
    }
  }
}

/** @brief Verify that accessing entire row returns the right values. */
TEST(Matrix, EntireRowAccess) {
  // Initialize the matrix with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Matrix<double> m{r, c, data};

  // Assert accessing rows is correct.
  double num = 1.0;
  for (size_t i = 0; i < r; i++) {
    std::vector<double> rowData = m.getRow(i);
    std::vector<double> expected{num, num + 1.0, num + 2.0};

    for (size_t j = 0; j < expected.size(); j++) {
      ASSERT_NEAR(rowData[j], expected[j], PRECISION_ERROR);
    }

    num += 3.0;
  }
}

/** @brief Verify that accessing entire columns returns the right values. */
TEST(Matrix, EntireColAccess) {
  // Initialize the matrix with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Matrix<double> m{r, c, data};

  // Assert accessing columns is correct.
  double num = 1.0;
  for (size_t i = 0; i < c; i++) {
    std::vector<double> colData = m.getCol(i);
    std::vector<double> expected{num, num + 3.0};

    for (size_t j = 0; j < expected.size(); j++) {
      ASSERT_NEAR(colData[j], expected[j], PRECISION_ERROR);
    }

    num += 1.0;
  }
}

/** @brief Verify an assertion is thrown when there is incorrect matrix
 * dimension during adding two matrices. */
TEST(Matrix, AdditionnIncorrectDim) {
  // Initialize 2 matrices with different dimensions.
  Matrix<double> m1{3, 4};
  Matrix<double> m2{4, 5};

  std::string assertStr =
      "Matrix elementwise addition have incorrect dimensions.";

  ASSERT_DEATH(m1 + m2, assertStr);
  ASSERT_DEATH(m1 += m2, assertStr);
}

/** @brief Verify that element wise addition works correctly. */
TEST(Matrix, ElementWiseAddition) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data1{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  std::vector<double> data2{2.0, 6.0, 7.0, 2.0, 9.0, 6.0};
  Matrix<double> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<double> data3{3.0, 8.0, 10.0, 6.0, 14.0, 12.0};
  Matrix<double> expected{r, c, data3};

  // Apply addition and assert that the result is near the expected
  // matrix.
  Matrix<double> result = m1 + m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(result(i, j), expected(i, j), PRECISION_ERROR);
    }
  }
}

/** @brief Verify that element wise additiona in place works correctly. */
TEST(Matrix, ElementWiseAdditionInPlace) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data1{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  std::vector<double> data2{2.0, 6.0, 7.0, 2.0, 9.0, 6.0};
  Matrix<double> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<double> data3{3.0, 8.0, 10.0, 6.0, 14.0, 12.0};
  Matrix<double> expected{r, c, data3};

  // Apply addition and assert that the result is near the expected
  // matrix.
  m1 += m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(m1(i, j), expected(i, j), PRECISION_ERROR);
    }
  }
}

/** @brief Verify that element wise addition with complex double works
 * correctly. */
TEST(Matrix, ComplexAddition) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 2;
  std::vector<DoubleComplex> data1{
      {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}};
  std::vector<double> data2{2.0, 2.0, 2.0, 2.0};
  Matrix<DoubleComplex> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<DoubleComplex> data3{
      {3.0, 2.0}, {5.0, 4.0}, {7.0, 6.0}, {9.0, 8.0}};
  Matrix<DoubleComplex> expected{r, c, data3};

  // Apply addition and assert that the result is near the expected
  // matrix.
  m1 += m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(m1(i, j).real(), expected(i, j).real(), PRECISION_ERROR);
      ASSERT_NEAR(m1(i, j).imag(), expected(i, j).imag(), PRECISION_ERROR);
    }
  }
}

/** @brief Verify an assertion is thrown when there is incorrect matrix
 * dimension during multiply two matrices. */
TEST(Matrix, MultiplicationIncorrectDim) {
  // Initialize 2 matrices with different dimensions.
  Matrix<double> m1{5, 4};
  Matrix<double> m2{4, 5};

  std::string assertStr =
      "Matrix elementwise multiplication have incorrect dimensions.";

  ASSERT_DEATH(m1 * m2, assertStr);
  ASSERT_DEATH(m1 *= m2, assertStr);
}

/** @brief Verify that element wise multiplication works correctly. */
TEST(Matrix, ElementWiseMultiplication) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data1{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  std::vector<double> data2{2.0, 6.0, 7.0, 2.0, 9.0, 6.0};
  Matrix<double> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<double> data3{2.0, 12.0, 21.0, 8.0, 45.0, 36.0};
  Matrix<double> expected{r, c, data3};

  // Apply multiplication and assert that the result is near the expected
  // matrix.
  Matrix<double> result = m1 * m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(result(i, j), expected(i, j), PRECISION_ERROR);
    }
  }
}

/** @brief Verify that element wise multiplication in place works correctly. */
TEST(Matrix, ElementWiseMultiplicationInPlace) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data1{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  std::vector<double> data2{2.0, 6.0, 7.0, 2.0, 9.0, 6.0};
  Matrix<double> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<double> data3{2.0, 12.0, 21.0, 8.0, 45.0, 36.0};
  Matrix<double> expected{r, c, data3};

  // Apply multiplication and assert that the result is near the expected
  // matrix.
  m1 *= m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(m1(i, j), expected(i, j), PRECISION_ERROR);
    }
  }
}

/** @brief Verify that element wise multiplication with complex double works
 * correctly. */
TEST(Matrix, ComplexMultiplication) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 2;
  std::vector<DoubleComplex> data1{
      {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}};
  std::vector<double> data2{2.0, 2.0, 2.0, 2.0};
  Matrix<DoubleComplex> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<DoubleComplex> data3{
      {2.0, 4.0}, {6.0, 8.0}, {10.0, 12.0}, {14.0, 16.0}};
  Matrix<DoubleComplex> expected{r, c, data3};

  // Apply multiplication and assert that the result is near the expected
  // matrix.
  m1 *= m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(m1(i, j).real(), expected(i, j).real(), PRECISION_ERROR);
      ASSERT_NEAR(m1(i, j).imag(), expected(i, j).imag(), PRECISION_ERROR);
    }
  }
}

/** @brief Verify an assertion is thrown when there is incorrect matrix
 * dimension during division of two matrices. */
TEST(Matrix, DivisionIncorrectDim) {
  // Initialize 2 matrices with different dimensions.
  Matrix<double> m1{5, 4};
  Matrix<double> m2{4, 5};

  std::string assertStr =
      "Matrix elementwise division have incorrect dimensions.";

  ASSERT_DEATH(m1 / m2, assertStr);
  ASSERT_DEATH(m1 /= m2, assertStr);
}

/** @brief Verify that element wise division works correctly. */
TEST(Matrix, ElementWiseDivision) {
  // Initialize 2 matrices with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data1{2.0, 12.0, 14.0, 4.0, 9.0, 24.0};
  std::vector<double> data2{2.0, 6.0, 7.0, 2.0, 9.0, 6.0};
  Matrix<double> m1{r, c, data1};
  Matrix<double> m2{r, c, data2};

  // Initialize expected matrix result.
  std::vector<double> data3{1.0, 2.0, 2.0, 2.0, 1.0, 4.0};
  Matrix<double> expected{r, c, data3};

  // Apply division and assert that the result is near the expected matrix.
  Matrix<double> result = m1 / m2;

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(result(i, j), expected(i, j), PRECISION_ERROR);
    }
  }
}

/** @brief Verify that matrix transpose works correctly for a sample matrix.. */
TEST(Matrix, Transpose) {
  // Initialize 2 matrices with data.
  size_t r = 3;
  size_t c = 3;
  std::vector<double> data1{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  std::vector<double> data2{1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0};
  Matrix<double> A{r, c, data1};
  Matrix<double> expected{r, c, data2};

  // Transpose the matrix and verify that the result is near the expected
  // matrix.

  Matrix<double> result = transpose(A);

  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      ASSERT_NEAR(result(i, j), expected(i, j), PRECISION_ERROR);
    }
  }
}
