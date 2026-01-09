/**
 *******************************************************************************
 * @file    beat_spectrum.cpp
 * @brief   Beat spectrum souce.
 *******************************************************************************
 */

#include "beat_spectrum.h"
#include "constants.h"

std::vector<double> createBeatSpectrum(const Matrix<double>& powerSpectrum) {
  size_t numTimeFrames = powerSpectrum.getNumRows();
  size_t numFreq = powerSpectrum.getNumCols();

  std::vector<double> b(numTimeFrames);

  // Create condensed beat spectrum.
  for (size_t j = 0; j < numTimeFrames; j++) {
    for (size_t i = 0; i < numFreq; i++) {
      double corr = 0.0;

      // Compute the beat spectrum correlation.
      for (size_t k = 0; k < numTimeFrames - j; k++) {
        corr += powerSpectrum(k, i) * powerSpectrum(k + j, i);
      }

      corr /= (numTimeFrames - j);
      b[j] += corr;
    }

    b[j] /= numFreq;
  }

  // Normalize beat spectrum.
  if (std::abs(b[0]) > DOUBLE_EPS) {
    for (double& i : b) {
      i /= b[0];
    }
  }

  return b;
}
