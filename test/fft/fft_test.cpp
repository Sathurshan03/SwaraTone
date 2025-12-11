/**
 ******************************************************************************
 * @file    fft_test.cpp
 * @brief   Unit tests for Fast Fourier Transform (FFT).
 ******************************************************************************
 */
#include "fft.h"

#include <gtest/gtest.h>

#include "frequencyDomain.h"
#include "test_helper.h"

/** @brief Given an impulse signal, expect FFT to return constant value for all
 * frequencies. */
TEST(fft, Impulse) {
  // Create impulse signal.
  double x[]{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  uint32_t N = static_cast<uint32_t>(sizeof(x) / sizeof(x[0]));

  // Run FFT on the signal.
  frequencyDomain X;
  initFrequncyDomain(N, X);
  runFFT(x, N, X);

  // Assert that there is a constant frequency value.
  const double constFreq = std::fabs(X.frequency[0]);
  for (int i = 0; i < N / 2; i++) {
    ASSERT_NEAR(std::fabs(X.frequency[i]), constFreq, PRECISION_ERROR);
  }
}

/** @brief Given a constant signal, the only frequency component is 0 Hz. */
TEST(fft, DC) {
  // Create constant signal.
  double x[]{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  uint32_t N = static_cast<uint32_t>(sizeof(x) / sizeof(x[0]));

  // Run FFT on the signal.
  frequencyDomain X;
  initFrequncyDomain(N, X);
  runFFT(x, N, X);

  // Assert that 0Hz has an amplitude.
  ASSERT_GT(std::fabs(X.frequency[0]), PRECISION_ERROR);

  // Assert that all other frequency has no amplitude.
  for (int i = 1; i < N / 2; i++) {
    ASSERT_LT(std::fabs(X.frequency[i]), PRECISION_ERROR);
  }
}
