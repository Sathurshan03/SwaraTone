/**
 *******************************************************************************
 * @file    beat_spectrum.cpp
 * @brief   Beat spectrum souce.
 *******************************************************************************
 */

#include "beat_spectrum.h"

#include <iostream>

#include "constants.h"

constexpr int MAX_LAG = 500;

std::vector<double> createBeatSpectrum(const Matrix<double>& powerSpectrum) {
  std::cout << "entered" << std::endl;
  size_t numTimeFrames = powerSpectrum.getNumRows();
  size_t numFreq = powerSpectrum.getNumCols();

  size_t maxLag = std::min<size_t>(MAX_LAG, numTimeFrames - 1);

  std::vector<double> beatSpectrum(maxLag, 0.0);

  // Create condensed beat spectrum.
  for (size_t lag = 0; lag < maxLag; lag++) {
    std::cout << "lag: " << lag << " numTimeFrame: " << maxLag << std::endl;
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
  std::cout << "exited loop" << std::endl;

  // Normalize beat spectrum.
  if (std::abs(beatSpectrum[0]) > DOUBLE_EPS) {
    double normalizationFactor = std::abs(beatSpectrum[0]) + 1e-12;
    for (double& value : beatSpectrum) {
      value /= normalizationFactor;
    }
  }

  return beatSpectrum;
}
