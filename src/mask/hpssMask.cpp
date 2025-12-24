/**
 *******************************************************************************
 * @file    hpssMask.cpp
 * @brief   HPSS (Harmonic Percussive Source Seperation) mask source.
 *******************************************************************************
 */

#include "hpssMask.hpp"

void applyBinaryMask(const Matrix<double>& yH, const Matrix<double>& yP,
                     Matrix<double>& mH, Matrix<double>& mP) {
  // Resize masks if needed.
  if (mH.size() != yH.size()) {
    mH.resize(yH.size());
  }

  if (mP.size() != yP.size()) {
    mP.resize(yP.size());
  }

  const size_t numOps = yH.getNumRows() * yH.getNumCols();

  // Apply binary mask.
  for (size_t i = 0; i < numOps; i++) {
    binaryMask(yH(i), yP(i), mH(i), mP(i));
  }
}

void applySoftMask(const Matrix<double>& yH, const Matrix<double>& yP,
                   Matrix<double>& mH, Matrix<double>& mP) {
  // Resize masks if needed.
  if (mH.size() != mH.size()) {
    mH.resize(yH.size());
  }

  if (mP.size() != mP.size()) {
    mP.resize(yP.size());
  }

  const size_t numOps = yH.getNumRows() * yH.getNumCols();

  // Apply soft mask.
  for (size_t i = 0; i < numOps; i++) {
    softMask(yH(i), yP(i), mH(i), mP(i));
  }
}
