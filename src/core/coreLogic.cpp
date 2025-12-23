/**
 *******************************************************************************
 * @file    coreLogic.cpp
 * @brief   Core logic source code.
 *******************************************************************************
 */

#include "coreLogic.h"

#include "constants.h"
#include "fft_helper.hpp"
#include "hpss.h"
#include "matrix.hpp"
#include "mp3.h"
#include "spectrum.h"

void runCore(std::string filePath) {
  // Read audio input from MP3 file.
  MP3Data mp3Data = readMP3File(filePath);

  // Determine size of spectrums. Subtract 1 from number windows to avoid
  // partially filled window.
  const size_t numFreqBins = getNyquistSize(WINDOW_SIZE);
  const size_t numWindows = (mp3Data.numSamples / HALF_WINDOW_SIZE) - 1;
  const size_t r = numFreqBins;
  const size_t c = numWindows;

  Matrix<std::complex<double>> complexSpectrum{r, c};
  Matrix<double> powerSpectrum{r, c};

  // Compute complex and power spectrum.
  LOG_INFO("Creating complex and power spectrum.");
  createComplexSpectrum(mp3Data.channel1, complexSpectrum, WINDOW_SIZE);
  createPowerSpectrum(complexSpectrum, powerSpectrum);

  // Apply HPSS.
  Matrix<std::complex<double>> hComplexSpectrum{};
  Matrix<std::complex<double>> pComplexSpectrum{};
  std::tie(hComplexSpectrum, pComplexSpectrum) =
      runHPSS(complexSpectrum, powerSpectrum);

  // Reconstruct signal
  // TODO.
}
