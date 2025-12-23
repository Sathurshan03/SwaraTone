/**
 *******************************************************************************
 * @file    hpssMask.h
 * @brief   HPSS (Harmonic Percussive Source Seperation) mask header.
 *******************************************************************************
 */

#pragma once

#include "matrix.hpp"

static const double epsilon = 0.0000001;
static const double epsilonHalf = epsilon / 2.0;

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
  double denominator = yH + yP + epsilon;
  mH = (yH + epsilonHalf) / denominator;
  mP = (yP + epsilonHalf) / denominator;
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
void applyBinaryMask(const Matrix& yH, const Matrix& yP, Matrix& mH,
                     Matrix& mP);

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
void applySoftMask(const Matrix& yH, const Matrix& yP, Matrix& mH, Matrix& mP);
