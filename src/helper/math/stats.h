/**
 *******************************************************************************
 * @file    stats.h
 * @brief   Statistics header file.
 *******************************************************************************
 */

#pragma once

#include <algorithm>
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
