/**
 *******************************************************************************
 * @file    beat_soft_mask.cpp
 * @brief   Beat soft mask source.
 *******************************************************************************
 */

#include "beat_soft_mask.h"

#include <algorithm>

#include "constants.h"
#include "stats.h"

Matrix<std::complex<double>> applySoftMask(
    const Matrix<double>& magnitudeSpectrogram,
    const Matrix<std::complex<double>>& X, size_t period) {
  size_t numFreqBins = magnitudeSpectrogram.getNumRows();
  size_t numTimeFrames = magnitudeSpectrogram.getNumCols();
  size_t numElements = magnitudeSpectrogram.getNumElements();

  assert(period < numTimeFrames);

  // Create repeating segment matrix (S).
  Matrix<double> repeatingSegment(numFreqBins, period);
  std::vector<double> periodMagnitudes;
  periodMagnitudes.reserve(numTimeFrames / period + 1);

  for (size_t freq = 0; freq < numFreqBins; freq++) {
    for (size_t periodOffset = 0; periodOffset < period; periodOffset++) {
      size_t numPeriodFrames =
          (numTimeFrames - periodOffset + period - 1) / period;
      periodMagnitudes.clear();
      periodMagnitudes.resize(numPeriodFrames);

      for (size_t i = 0; i < numPeriodFrames; i++) {
        periodMagnitudes.push_back(
            magnitudeSpectrogram(freq, periodOffset + i * period));
      }
      repeatingSegment(freq, periodOffset) = median(periodMagnitudes);
    }
  }

  // Create repeating weight matix (W).
  Matrix<double> repeatWeight(numFreqBins, numTimeFrames);

  std::vector<double> runningMin(
      period, MAX_DOUBLE);  // Track min magnitude per period offset.
  for (size_t freq = 0; freq < numFreqBins; freq++) {
    for (int frame = static_cast<int>(numTimeFrames) - 1; frame >= 0; frame--) {
      size_t offset = frame % period;
      runningMin[offset] =
          std::min(runningMin[offset], magnitudeSpectrogram(freq, frame));
      repeatWeight(freq, frame) =
          std::min(repeatingSegment(freq, offset), runningMin[offset]);
    }
  }

  // Create soft mask (M).
  Matrix<double> maskMatrix(numFreqBins, numTimeFrames);
  Matrix<std::complex<double>> maskedX(numFreqBins, numTimeFrames);

  for (size_t i = 0; i < numElements; i++) {
    if (magnitudeSpectrogram(i) > DOUBLE_EPS) {
      maskMatrix(i) =
          std::clamp(repeatWeight(i) / magnitudeSpectrogram(i), 0.0, 1.0);
    }
  }

  // Apply M onto STFT X.
  maskedX = X * maskMatrix;

  return maskedX;
}
