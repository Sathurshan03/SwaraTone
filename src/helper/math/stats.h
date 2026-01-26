/**
 *******************************************************************************
 * @file    stats.h
 * @brief   Statistics header file.
 *******************************************************************************
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

/**
 * @brief Computes the median from a list.
 *
 * @tparam T Type of vector.
 * @param[in] vec Vector to compute the median on.
 * @return T The median in the list.
 */
template <typename T>
T median(std::vector<T>& vec) {
  std::vector<T> cpyVec(vec);
  std::sort(std::begin(cpyVec), std::end(cpyVec));

  size_t midPos = cpyVec.size() / 2;

  if (cpyVec.size() % 2 == 0) {
    return (cpyVec[midPos] + cpyVec[midPos - 1]) / 2;
  } else {
    return cpyVec[midPos];
  }
}

/**
 * @brief Return the index of the maximum value within a specified range of a
 * vector.
 *
 * @tparam T The type of the vector.
 * @param vec Vector to serach max value.
 * @param startIdx The starting index to start search. (inclusive)
 * @param endIdx The index to end search. (exclusive)
 * @return size_t The index of the maximum value within the range. Returns -1 if
 * invalid input parameters.
 */
template <typename T>
size_t argmax(const std::vector<T>& vec, size_t startIdx, size_t endIdx) {
  // Check input parameter validity.
  if (startIdx > endIdx || startIdx >= vec.size() || endIdx > vec.size() ||
      vec.size() == 0) {
    return size_t(-1);
  }

  T maxValue = vec[startIdx];
  size_t maxIdx = startIdx;
  for (size_t i = startIdx; i < endIdx; i++) {
    if (vec[i] > maxValue) {
      maxValue = vec[i];
      maxIdx = i;
    }
  }

  return maxIdx;
}
