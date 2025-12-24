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

  // Apply binary mask.
  for (int i = 0; i < yH.getNumRows(); i++) {
    for (int j = 0; j < yH.getNumCols(); j++) {
      binaryMask(yH(i, j), yP(i, j), mH(i, j), mP(i, j));
    }
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

  // Apply soft mask.
  for (int i = 0; i < yH.getNumRows(); i++) {
    for (int j = 0; j < yH.getNumCols(); j++) {
      softMask(yH(i, j), yP(i, j), mH(i, j), mP(i, j));
    }
  }
}
