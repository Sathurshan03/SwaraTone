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

  std::vector<double> beatSpectrum(numTimeFrames);

  // Create condensed beat spectrum.
  for (size_t lag = 0; lag < numTimeFrames; lag++) {
    for (size_t freqBin = 0; freqBin < numFreq; freqBin++) {
      double lagCorrelation = 0.0;

      // Compute the beat spectrum correlation.
      for (size_t timeIndex = 0; timeIndex < numTimeFrames - lag; timeIndex++) {
        lagCorrelation += powerSpectrum(timeIndex, freqBin) *
                          powerSpectrum(timeIndex + lag, freqBin);
      }

      lagCorrelation /= (numTimeFrames - lag);
      beatSpectrum[lag] += lagCorrelation;
    }

    beatSpectrum[lag] /= numFreq;
  }

  // Normalize beat spectrum.
  if (std::abs(beatSpectrum[0]) > DOUBLE_EPS) {
    double normalizationFactor = std::abs(beatSpectrum[0]) + 1e-12;
    for (double& value : beatSpectrum) {
      value /= normalizationFactor;
    }
  }

  return beatSpectrum;
}
