/**
 *******************************************************************************
 * @file    beat_soft_mask.cpp
 * @brief   Beat soft mask source.
 *******************************************************************************
 */

#include "beat_soft_mask.h"

Matrix<std::complex<double>> applySoftMask(
    const Matrix<double>& W, const Matrix<double>& V,
    const Matrix<std::complex<double>>& X) {
  // Crease soft mask.
  Matrix<double> M(W.getNumRows(), W.getNumCols());
  Matrix<std::complex<double>> maskedX(W.getNumRows(), W.getNumCols());
  M = W / V;

  // Symmetrize M.
  M = (M + transpose(M));
  M.scale(0.5);

  // Apply M onto STFT X.
  maskedX = X * M;

  return maskedX;
}
