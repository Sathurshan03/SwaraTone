/**
 *******************************************************************************
 * @file    matrix.h
 * @brief   Matrix header file.
 *******************************************************************************
 */

#pragma once

#include <cassert>
#include <vector>

#include "logging.h"

/** @brief Matrix class. */
template <typename T>
class Matrix {
 public:
  /** @brief Construct a new Matrix object. */
  Matrix() {
    rows = 1;
    cols = 1;
    data.resize(1);
  }

  /**
   * @brief Construct a new Matrix object.
   *
   * @param[in] rows The number of rows.
   * @param[in] cols The number of columns.
   */
  Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows * cols, 0.0);
  }

  /**
   * @brief Construct a new Matrix object.
   *
   * @param[in] rows The number of rows.
   * @param[in] cols The number of columns.
   * @param[in] data Data to initialize matrix to.
   */
  Matrix(size_t rows, size_t cols, std::vector<T> data)
      : rows(rows), cols(cols), data(data) {
    if (data.size() != rows * cols) {
      // Set to vector is matrix dimension does not make sense.
      rows = data.size();
      cols = 1;
      LOG_WARNING("Matrix dimension does not fit. Setting matrix to vector.");
    }
  }

  /**
   * @brief Single cell access.
   *
   * @param[in] i row number.
   * @param[in] j column number.
   * @return T& value at cell (i, j).
   */
  inline T& operator()(size_t i, size_t j) { return data[i * cols + j]; }

  /**
   * @brief Single cell access.
   *
   * @param[in] i row number.
   * @param[in] j column number.
   * @return T& value at cell (i, j).
   */
  inline const T& operator()(size_t i, size_t j) const {
    return data[i * cols + j];
  }

  /**
   * @brief Matrix element-wise addition. A += B
   *
   * @param b matrix to add with B.
   * @return Matrix<T>& Result A.
   */
  Matrix<T>& operator+=(const Matrix<T>& b) {
    assert(this->size() == b.size() &&
           "Matrix elementwise addition have incorrect dimensions.");

    for (size_t i = 0; i < data.size(); i++) {
      data[i] += b.data[i];
    }
    return *this;
  }

  /**
   * @brief Matrix element-wise multiplication. A *= B
   *
   * @param b multiplier matrix B.
   * @return Matrix<T>& Result A.
   */
  Matrix<T>& operator*=(const Matrix<T>& b) {
    assert(this->size() == b.size() &&
           "Matrix elementwise multiplication have incorrect dimensions.");

    for (size_t i = 0; i < data.size(); i++) {
      data[i] *= b.data[i];
    }
    return *this;
  }

  /**
   * @brief Returns the size of the matrix.
   *
   * @return std::pair<size_t, size_t> Pair where first item is number of rows
   * and second item is number of columns.
   */
  inline std::pair<size_t, size_t> size() const {
    return std::make_pair(rows, cols);
  }

  /**
   * @brief Resizes the matrix.
   *
   * @param[in] newSize Pair where the first item is number of rows and second
   * item is number of columns.
   */
  void resize(std::pair<size_t, size_t> newSize) {
    if (rows != newSize.first || cols != newSize.second) {
      rows = newSize.first;
      cols = newSize.second;
      data.resize(rows * cols);
    }
  }

  /**
   * @brief Return the number of rows in the matrix.
   *
   * @return size_t The number of rows.
   */
  inline size_t getNumRows() const { return rows; }

  /**
   * @brief Return the number of columns in the matrix.
   *
   * @return size_t The number of columns.
   */
  inline size_t getNumCols() const { return cols; }

  /**
   * @brief Get a copy of the entire row.
   *
   * @param[in] r Row number.
   * @return std::vector<T> Row content.
   */
  std::vector<T> getRow(size_t r) const {
    assert(r < rows);
    std::vector<T> rowData(cols);

    std::copy(data.begin() + r * cols, data.begin() + r * cols + cols,
              rowData.begin());

    return rowData;
  }

  /**
   * @brief Get a copy of the entire column.
   *
   * @param[in] c Column number.
   * @return std::vector<T> Column content.
   */
  std::vector<T> getCol(size_t c) {
    assert(c < cols);
    std::vector<T> colData(rows);

    for (size_t i = 0; i < rows; i++) colData[i] = data[i * cols + c];

    return colData;
  }

 private:
  /** @brief The number of rows in the matrix. */
  size_t rows{0};

  /** @brief The number of columns in the matrix. */
  size_t cols{0};

  /** @brief Matrix data. Data is stored linearly. Cell (i, j) = i * cols + j */
  std::vector<T> data{};
};

/**
 * @brief Matrix element-wise addition. A = C * B
 *
 * @param c original matrix C.
 * @param b matrix to add with B.
 * @return Matrix<T>& Result A.
 */
template <typename T>
Matrix<T> operator+(Matrix<T> c, const Matrix<T>& b) {
  c += b;
  return c;
}

/**
 * @brief Matrix element-wise multiplication. A = C * B
 *
 * @param c original matrix C.
 * @param b multiplier matrix B.
 * @return Matrix<T>& Result A.
 */
template <typename T>
Matrix<T> operator*(Matrix<T> c, const Matrix<T>& b) {
  c *= b;
  return c;
}