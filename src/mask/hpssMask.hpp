/**
 *******************************************************************************
 * @file    hpssMask.h
 * @brief   HPSS (Harmonic Percussive Source Seperation) mask header.
 *******************************************************************************
 */

#pragma once

#include <cmath>

#include "constants.h"
#include "matrix.hpp"

static const double epsilon = DOUBLE_EPS * 2;
static const double epsilonHalf = DOUBLE_EPS;
static const double softMaskExp = 0.75;

/**
 * @brief Applies binary mask.
 *
 * @param[in] yH Harmonic median estimate.
 * @param[in] yP Percussive median estimate.
 * @param[out] mH Binary mask for harmonic component.
 * @param[out] mP Binary mask for percussive component.
 */
inline void binaryMask(const double yH, const double yP, double& mH,
                       double& mP) {
  if (yH >= yP) {
    mH = 1.0;
    mP = 0.0;
  } else {
    mH = 0.0;
    mP = 1.0;
  }
}

/**
 * @brief Applies soft mask.
 *
 * @param[in] yH Harmonic median estimate.
 * @param[in] yP Percussive median estimate.
 * @param[out] mH Soft mask for harmonic component.
 * @param[out] mP Soft mask for percussive component.
 */
inline void softMask(const double yH, const double yP, double& mH, double& mP) {
  double denominator =
      std::pow(yH, softMaskExp) + std::pow(yP, softMaskExp) + epsilon;

  mH = (std::pow(yH, softMaskExp) + epsilonHalf) / denominator;
  mP = (std::pow(yP, softMaskExp) + epsilonHalf) / denominator;
}

/**
 * @brief Applies a binary mask to separate harmonic and percussive components.
 *
 * Compares the harmonic and percussive median estimates and assigns each
 * time–frequency bin exclusively to either the harmonic or percussive mask.
 *
 * @param[in] yH Harmonic median estimates.
 * @param[in] yP Percussive median estimates.
 * @param[out] mH Binary mask for harmonic components.
 * @param[out] mP Binary mask for percussive components.
 */
void applyBinaryMask(const Matrix<double>& yH, const Matrix<double>& yP,
                     Matrix<double>& mH, Matrix<double>& mP);

/**
 * @brief Applies a soft mask to separate harmonic and percussive components.
 *
 * Computes continuous-valued masks that determine the relative contribution
 * of harmonic and percussive components in each time–frequency bin.
 *
 * @param[in] yH Harmonic median estimates.
 * @param[in] yP Percussive median estimates.
 * @param[out] mH Soft mask for harmonic components.
 * @param[out] mP Soft mask for percussive components.
 */
void applySoftMask(const Matrix<double>& yH, const Matrix<double>& yP,
                   Matrix<double>& mH, Matrix<double>& mP);

/**
 * @brief Applies a soft mask to separate harmonic and percussive components to
 * subset of matrix.
 *
 * Computes continuous-valued masks that determine the relative contribution
 * of harmonic and percussive components in each time–frequency bin.
 *
 * @param[in] yH Harmonic median estimates.
 * @param[in] yP Percussive median estimates.
 * @param[out] mH Soft mask for harmonic components.
 * @param[out] mP Soft mask for percussive components.
 * @param[in] start Starting index of matrix to apply soft mask. The index is
 * following 1D representation of the matrix.
 * @param[in] end Ending index (non-inclusive) of matrix to apply soft mask. The
 * index is following 1D representation of the matrix.
 */
void applySoftMaskSubset(const Matrix<double>& yH, const Matrix<double>& yP,
                         Matrix<double>& mH, Matrix<double>& mP, size_t start,
                         size_t end);
