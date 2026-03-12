/**
 *******************************************************************************
 * @file    beat_spectrum.cpp
 * @brief   Beat spectrum souce.
 *******************************************************************************
 */

#include "beat_spectrum.h"

#include <iostream>
#include <thread>

#include "constants.h"

constexpr int MAX_LAG = 500;  // ~11.6 s = MAX_LAG / (SAMPLE_RATE / HOP_SIZE)

std::vector<double> createBeatSpectrum(const Matrix<double>& powerSpectrum) {
  size_t numTimeFrames = powerSpectrum.getNumRows();
  size_t numFreq = powerSpectrum.getNumCols();

  size_t maxLag = std::min<size_t>(MAX_LAG, numTimeFrames - 1);

  std::vector<double> beatSpectrum(maxLag, 0.0);
  std::vector<std::thread> threads;
  threads.reserve(maxLag);

  // Create condensed beat spectrum.
  // TODO: Up to 500 threads are being created. Limit to couple of threads and
  // let each thread handle multiple rows.
  for (size_t lag = 0; lag < maxLag; lag++) {
    threads.emplace_back(
        std::thread(computeBeatSpectrumThread, lag, numTimeFrames, numFreq,
                    std::ref(powerSpectrum), std::ref(beatSpectrum)));
  }

  for (std::thread& thread : threads) {
    thread.join();
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

void computeBeatSpectrumThread(size_t lag, size_t numTimeFrames, size_t numFreq,
                               const Matrix<double>& powerSpectrum,
                               std::vector<double>& beatSpectrum) {
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
