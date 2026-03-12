/**
 *******************************************************************************
 * @file    repet.cpp
 * @brief   REpeating Pattern Extraction Technique (REPET) source code.
 *******************************************************************************
 */

#include "beat_soft_mask.h"
#include "beat_spectrum.h"
#include "logging.h"
#include "matrix.hpp"
#include "repeating_period.h"

Matrix<std::complex<double>> runRepet(const Matrix<double>& magnitudeSpectrum,
                                      const Matrix<double>& powerSpectrum,
                                      const Matrix<std::complex<double>>& X) {
  LOG_INFO("Running REPET.");

  LOG_INFO("Creating breat spectrum.");
  std::vector<double> beatSpectrum = createBeatSpectrum(powerSpectrum);

  LOG_INFO("Finding period.");
  size_t period = static_cast<size_t>(findRepeatingPeriod(beatSpectrum));

  LOG_INFO("Applying mask.");
  Matrix<std::complex<double>> maskedX;
  applySoftMask(magnitudeSpectrum, X, period, maskedX);

  LOG_INFO("Finished running REPET.");

  return maskedX;
}
