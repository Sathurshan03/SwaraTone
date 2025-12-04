/**
 *******************************************************************************
 * @file    frequencyDomain.h
 * @brief   Frequency domain header.
 *******************************************************************************
 */

#pragma once

#include <complex>
#include <cstdint>
#include <vector>

/** @brief Structure to hold frequency domain data. */
struct frequencyDomain {
  /** @brief Frequency data represented in complex plane. */
  std::vector<std::complex<double>> frequency{};

  /**
   * @brief The number of frequency bins being represented. That is the
   * difference of each bin will be max frequency / numbins.
   */
  uint16_t numBins = 0;
};

/**
 * @brief Initializes the frequency domain struct.
 *
 * @param windowSize The size of the input window.
 * @param X Frequency domain struct to initialize.
 */
void initFrequncyDomain(uint16_t windowSize, frequencyDomain& X);
