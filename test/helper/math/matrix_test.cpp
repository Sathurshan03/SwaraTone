/**
 ******************************************************************************
 * @file    matrix_test.cpp
 * @brief   Unit tests for Matrix class.
 ******************************************************************************
 */

#include "matrix.hpp"

#include <gtest/gtest.h>

#include "test_helper.h"

/** @brief Tests matrix dimensions are correct at initialization. */
TEST(Matrix, Dimension) {
  // Initialize a matrix.
  size_t r = 9;
  size_t c = 3;
  Matrix m{r, c};

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
  Matrix m{r, c};

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
  // Initial the matrix with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Matrix m{r, c, data};

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
  // Initial the matrix with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Matrix m{r, c, data};

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
  // Initial the matrix with data.
  size_t r = 2;
  size_t c = 3;
  std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Matrix m{r, c, data};

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
