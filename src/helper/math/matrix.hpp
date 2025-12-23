/**
 *******************************************************************************
 * @file    matrix.h
 * @brief   Matrix header file.
 *******************************************************************************
 */

#pragma once

#include <vector>

/** @brief Matrix class. */
class Matrix {
 public:
  /**  @brief Construct a new Matrix object. */
  Matrix();

  /**
   * @brief Construct a new Matrix object.
   *
   * @param rows The number of rows.
   * @param cols The number of columns.
   */
  Matrix(size_t rows, size_t cols);

  /**
   * @brief Construct a new Matrix object.
   *
   * @param rows The number of rows.
   * @param cols The number of columns.
   * @param data Data to initialize matrix to.
   */
  Matrix(size_t rows, size_t cols, std::vector<double> data);

  /**
   * @brief Single cell access.
   *
   * @param i row number.
   * @param j column number.
   * @return double& value at cell (i, j).
   */
  inline double& operator()(size_t i, size_t j) { return data[i * cols + j]; }

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
   * @brief Resizes the matrix.
   *
   * @param newSize Pair where the first item is number of rows and second item
   * is number of columns.
   */
  void resize(std::pair<size_t, size_t> newSize);

  /**
   * @brief Single cell access.
   *
   * @param i row number.
   * @param j column number.
   * @return double& value at cell (i, j).
   */
  inline const double& operator()(size_t i, size_t j) const {
    return data[i * cols + j];
  }

  /**
   * @brief Get a copy of the entire row.
   *
   * @param row Row number.
   * @return std::vector<double> Row content.
   */
  std::vector<double> getRow(size_t row) const;

  /**
   * @brief Get a copy of the entire column.
   *
   * @param col Column number.
   * @return std::vector<double> Column content.
   */
  std::vector<double> getCol(size_t col);

 private:
  /** @brief The number of rows in the matrix. */
  size_t rows{0};

  /** @brief The number of columns in the matrix. */
  size_t cols{0};

  /** @brief Matrix data. Data is stored linearly. Cell (i, j) = i * cols + j */
  std::vector<double> data{};
};