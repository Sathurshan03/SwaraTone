/**
 *******************************************************************************
 * @file    matrix.cpp
 * @brief   Matrix source file.
 *******************************************************************************
 */

#include "matrix.hpp"

#include <cassert>

#include "logging.h"

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
  data.resize(rows * cols, 0.0);
}

Matrix::Matrix(size_t rows, size_t cols, std::vector<double> data)
    : rows(rows), cols(cols), data(data) {
  if (data.size() != rows * cols) {
    // Set to vector is matrix dimension does not make sense.
    rows = data.size();
    cols = 1;
    LOG_WARNING("Matrix dimension does not fit. Setting matrix to vector.");
  }
}

void Matrix::resize(std::pair<size_t, size_t> newSize) {
  rows = newSize.first;
  cols = newSize.second;
  data.resize(rows * cols);
}

std::vector<double> Matrix::getRow(size_t r) const {
  assert(r < rows);
  std::vector<double> rowData(cols);

  std::copy(data.begin() + r * cols, data.begin() + r * cols + cols,
            rowData.begin());

  return rowData;
}

std::vector<double> Matrix::getCol(size_t c) {
  assert(c < cols);
  std::vector<double> colData(rows);

  for (size_t i = 0; i < rows; i++) colData[i] = data[i * cols + c];

  return colData;
}
