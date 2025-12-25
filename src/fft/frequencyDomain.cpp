/**
 *******************************************************************************
 * @file    frequencyDomain.cpp
 * @brief   Frequency domain source.
 *******************************************************************************
 */

#include "frequencyDomain.h"

void initFrequncyDomain(uint32_t windowSize, frequencyDomain& X) {
  X.numBins = (windowSize / 2) + 1;
  X.frequency.reserve(windowSize);
}

void resizeFrequncyDomain(uint32_t newSize, frequencyDomain& X) {
  X.numBins = newSize;
  X.frequency.resize(X.numBins);
}
