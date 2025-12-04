/**
 *******************************************************************************
 * @file    frequencyDomain.cpp
 * @brief   Frequency domain source.
 *******************************************************************************
 */

#include "frequencyDomain.h"

void initFrequncyDomain(uint16_t windowSize, frequencyDomain& X) {
  X.numBins = windowSize / 2 + 1;
  X.frequency.resize(X.numBins);
}
