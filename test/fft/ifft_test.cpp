/**
 ******************************************************************************
 * @file    ifft_test.cpp
 * @brief   Unit tests for Inverse Fast Fourier Transform (IFFT).
 ******************************************************************************
 */
#include "ifft.h"

#include <gtest/gtest.h>

#include "test_helper.h"

/** @brief Given a frequency domain input where only the DC (0 Hz) component is
 * non-zero, the IFFT should produce a constant value in the time domain. */
TEST(ifft, ZeroFreq) {
  // Frequency domain representation with only DC component set to 1.
  std::vector<std::complex<double>> X{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  uint32_t N = static_cast<uint32_t>(X.size());

  // Compute the IFFT.
  std::vector<std::complex<double>> x;
  bool isNyquistApplied{false};
  runIFFT(X, N, x, isNyquistApplied);

  // Assert that all time-domain samples have approximately the same amplitude.
  const double amplitude = x[0].real();
  for (int i = 0; i < x.size(); i++) {
    ASSERT_NEAR(x[i].real(), amplitude, PRECISION_ERROR);
  }
}

/** @brief When all frequency bins are set to the same value, the IFFT should
 * produce an impulse in the time domain. */
TEST(fft, impulse) {
  // Frequency domain representation with all components set to 1.
  std::vector<std::complex<double>> X{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  uint32_t N = static_cast<uint32_t>(X.size());

  // Compute the IFFT.
  std::vector<std::complex<double>> x;
  bool isNyquistApplied{false};
  runIFFT(X, N, x, isNyquistApplied);

  // Verify that the first time-domain sample has significant amplitude.
  ASSERT_GT(x[0].real(), PRECISION_ERROR);

  // Assert that all other time-domain samples are effectively zero.
  for (int i = 1; i < x.size(); i++) {
    ASSERT_LT(x[i].real(), PRECISION_ERROR);
  }
}

/** @brief Given a frequency domain input where only the DC (0 Hz) component is
 * non-zero, Nquist theorem has been applied to the frequency input, the IFFT
 * should produce a constant value in the time domain. */
TEST(ifft, ZeroFreqNyquist) {
  // Frequency domain representation with only DC component set to 1.
  // Note that the frequency is represent using Nyquist theroem. Thus it holds
  // the first (N / 2) + 1 data points since IFFT requires powers of 2
  // datapoints for the entire frequency spectrum.
  std::vector<std::complex<double>> X{1.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0};
  uint32_t N = static_cast<uint32_t>(X.size());

  // Compute the IFFT.
  std::vector<std::complex<double>> x;
  bool isNyquistApplied{true};
  runIFFT(X, N, x, isNyquistApplied);

  // Assert that all time-domain samples have approximately the same amplitude.
  const double amplitude = x[0].real();
  for (int i = 0; i < x.size(); i++) {
    ASSERT_NEAR(x[i].real(), amplitude, PRECISION_ERROR);
  }
}

/** @brief When all frequency bins are set to the same value and Nquist theorem
 * has been applied to the frequency input, the IFFT should produce an impulse
 * in the time domain. */
TEST(fft, impulseNyquist) {
  // Frequency domain representation with all components set to 1.
  // Note that the frequency is represent using Nyquist theroem. Thus it holds
  // the first (N / 2) + 1 data points since IFFT requires powers of 2
  // datapoints for the entire frequency spectrum.
  std::vector<std::complex<double>> X{1.0, 1.0, 1.0, 1.0, 1.0,
                                      1.0, 1.0, 1.0, 1.0};
  uint32_t N = static_cast<uint32_t>(X.size());

  // Compute the IFFT.
  std::vector<std::complex<double>> x;
  bool isNyquistApplied{true};
  runIFFT(X, N, x, isNyquistApplied);

  // Verify that the first time-domain sample has significant amplitude.
  ASSERT_GT(x[0].real(), PRECISION_ERROR);

  // Assert that all other time-domain samples are effectively zero.
  for (int i = 1; i < x.size(); i++) {
    ASSERT_LT(x[i].real(), PRECISION_ERROR);
  }
}
