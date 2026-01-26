/**
 *******************************************************************************
 * @file    beat_soft_mask.cpp
 * @brief   Beat soft mask source.
 *******************************************************************************
 */

#include "beat_soft_mask.h"

#include <algorithm>

Matrix<std::complex<double>> applySoftMask(
    const Matrix<double>& repeatWeight, const Matrix<double>& totalEnergyMatrix,
    const Matrix<std::complex<double>>& X) {
  // Crease soft mask.
  Matrix<double> maskMatrix(repeatWeight.getNumRows(),
                            repeatWeight.getNumCols());
  Matrix<std::complex<double>> maskedX(repeatWeight.getNumRows(),
                                       repeatWeight.getNumCols());

  for (size_t i = 0; i < maskMatrix.getNumElements(); i++) {
    maskMatrix(i) =
        std::clamp(repeatWeight(i) / totalEnergyMatrix(i), 0.0, 1.0);
  }

  // Apply M onto STFT X.
  maskedX = X * maskMatrix;

  return maskedX;
}
