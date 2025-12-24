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
#include "signalReconstruction.h"
#include "spectrum.h"
#include "wav_encoding.h"

void runCore(std::string filePath) {
  // Read audio input from MP3 file.
  MP3Data mp3Data = readMP3File(filePath);

  // Determine size of spectrums. Input will include half a window size of
  // padding for smoothness.
  const size_t numFreqBins = getNyquistSize(WINDOW_SIZE);
  const size_t numWindows = (mp3Data.numSamples / HALF_WINDOW_SIZE) + 1;
  const size_t r = numFreqBins;
  const size_t c = numWindows;

  // Pad input.
  std::vector<double> input(mp3Data.numSamples + WINDOW_SIZE, 0.0);
  std::copy(mp3Data.channel1.begin(), mp3Data.channel1.end(),
            input.begin() + HALF_WINDOW_SIZE);

  Matrix<std::complex<double>> complexSpectrum{r, c};
  Matrix<double> powerSpectrum{r, c};

  // Compute complex and power spectrum.
  LOG_INFO("Creating complex and power spectrum.");
  createComplexSpectrum(input, complexSpectrum, WINDOW_SIZE);
  createPowerSpectrum(complexSpectrum, powerSpectrum);

  // Apply HPSS.
  Matrix<std::complex<double>> hComplexSpectrum{};
  Matrix<std::complex<double>> pComplexSpectrum{};
  std::tie(hComplexSpectrum, pComplexSpectrum) =
      runHPSS(complexSpectrum, powerSpectrum);

  // Reconstruct signals.
  LOG_INFO("Reconstructing signals.");
  std::vector<double> harmonics{};
  std::vector<double> percussive{};
  reconstructSignal(hComplexSpectrum, WINDOW_SIZE, harmonics);
  reconstructSignal(pComplexSpectrum, WINDOW_SIZE, percussive);

  // Save signals to audio file.
  LOG_INFO("Saving signals to audio");
  WAVFileEncoder wavEncoder{};
  wavEncoder.writeToFile("harmonics", harmonics, BITS_PER_SAMPLE, Channel::Mono,
                         SAMPLE_RATE);
  wavEncoder.writeToFile("percussive", percussive, BITS_PER_SAMPLE,
                         Channel::Mono, SAMPLE_RATE);
  LOG_INFO("Done core logic");
}
