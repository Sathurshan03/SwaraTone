/**
 *******************************************************************************
 * @file    repeating_period.cpp
 * @brief   Repeating period source code.
 *******************************************************************************
 */

#include "repeating_period.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>

#include "constants.h"
#include "stats.h"

const double SEARCH_RADIUS_FACTOR = 0.05;

int findRepeatingPeriod(const std::vector<double>& beatSpectrum) {
  size_t totalPeriods = beatSpectrum.size();
  size_t analysisLength = beatSpectrum.size() * 3 / 4;
  size_t maxPeriod = analysisLength / 3;
  std::vector<double> periodScores(maxPeriod, -1e9);

  // Accumulated sum vector. This is to speed up mean calculations. Values are
  // stored in index + 1, since end index in other parts of the algo are
  // exclusive.
  std::vector<double> accumSum(totalPeriods + 1, 0.0);
  for (size_t i = 0; i < totalPeriods; i++) {
    accumSum[i + 1] = accumSum[i] + beatSpectrum[i];
  }

  // Find the best period by scoring each of them.
  for (size_t candidatePeriod = 1; candidatePeriod < maxPeriod;
       candidatePeriod++) {
    size_t searchRadius =
        std::max<size_t>(1, SEARCH_RADIUS_FACTOR * candidatePeriod);
    size_t largeSearchRadius = 3U * candidatePeriod / 4U;
    double scoreSum = 0.0;

    // Check for peaks at all multiples of the candidate period.
    for (size_t expectedPeakIdx = candidatePeriod;
         expectedPeakIdx < totalPeriods; expectedPeakIdx += candidatePeriod) {
      // Search peaks within small window.
      size_t smallWindowStart =
          std::max<size_t>(expectedPeakIdx - searchRadius, 0);
      size_t smallWindowEnd =
          std::min<size_t>(expectedPeakIdx + searchRadius + 1, totalPeriods);

      size_t narrowPeakIdx =
          argmax(beatSpectrum, smallWindowStart, smallWindowEnd);

      // Search peaks within larger window.
      size_t largeWindowStart =
          std::max<size_t>(expectedPeakIdx - largeSearchRadius, 0);
      size_t largeWindowEnd = std::min<size_t>(
          expectedPeakIdx + largeSearchRadius + 1, totalPeriods);

      size_t broadPeakIdx =
          argmax(beatSpectrum, largeWindowStart, largeWindowEnd);

      // Add to score if the peak is the same for both windows.
      if (narrowPeakIdx != size_t(-1) && narrowPeakIdx == broadPeakIdx &&
          largeWindowStart != largeWindowEnd) {
        double windowSum =
            accumSum[largeWindowEnd] - accumSum[largeWindowStart];
        double windowMean = windowSum / (largeWindowEnd - largeWindowStart);

        scoreSum += beatSpectrum[narrowPeakIdx] - windowMean;
      }
    }

    // Save the score.
    int normalizationFactor = analysisLength / candidatePeriod;
    periodScores[candidatePeriod] =
        (normalizationFactor == 0) ? 0 : scoreSum / normalizationFactor;
  }

  int bestPeriod = static_cast<int>(argmax(periodScores, 1, maxPeriod));

  return bestPeriod;
}
