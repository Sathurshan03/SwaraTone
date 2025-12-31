/**
 *******************************************************************************
 * @file    coreLogic.cpp
 * @brief   Core logic source code.
 *******************************************************************************
 */

#include "coreLogic.h"

#include <filesystem>

#include "constants.h"
#include "fft_helper.hpp"
#include "highPass.h"
#include "hpss.h"
#include "matrix.hpp"
#include "mp3.h"
#include "signalReconstruction.h"
#include "spectrum.h"
#include "wav_encoding.h"

void runCore(std::string filePath) {
  // Read audio input from MP3 file.
  MP3Data mp3Data = readMP3File(filePath);

  // Determine size of spectrums. Input will include padding for smoothness.
  const size_t numFreqBins = getNyquistSize(WINDOW_SIZE);
  const size_t numWindows = (mp3Data.numSamples / HOP_SIZE) + 1;
  const size_t r = numWindows;
  const size_t c = numFreqBins;

  // Pad input.
  std::vector<double> input(mp3Data.numSamples + PADDING_SIZE * 2, 0.0);
  createInput(mp3Data, input);

  // Compute complex and power spectrum.
  LOG_INFO("Creating complex and power spectrum.");
  Matrix<std::complex<double>> complexSpectrum{r, c};
  Matrix<double> powerSpectrum{r, c};
  createComplexSpectrum(input, complexSpectrum);
  createPowerSpectrum(complexSpectrum, powerSpectrum);

  // Apply HPSS.
  Matrix<std::complex<double>> hComplexSpectrum{};
  Matrix<std::complex<double>> pComplexSpectrum{};
  runHPSS(complexSpectrum, powerSpectrum, hComplexSpectrum, pComplexSpectrum);

  // Reconstruct signals.
  LOG_INFO("Reconstructing signals.");
  std::vector<double> harmonics{};
  std::vector<double> percussive{};
  std::vector<double> vocals{};
  std::vector<double> vocalsFiltered{};
  reconstructSignal(hComplexSpectrum, harmonics);
  reconstructSignal(pComplexSpectrum, percussive);

  Matrix<std::complex<double>> vComplexSpectrum =
      hComplexSpectrum.scale(0.8) + pComplexSpectrum.scale(0.2);
  reconstructSignal(vComplexSpectrum, vocals);

  digitalHighPass(vocals, vocalsFiltered, VOICE_CUTOFF_HZ,
                  static_cast<double>(mp3Data.sampleRate_hz));

  // Save signals to audio file.
  LOG_INFO("Saving signals to audio");
  WAVFileEncoder wavEncoder{};
  std::string fileSuffix = std::filesystem::path(filePath).stem().string();
  wavEncoder.writeToFile("harmonics_" + fileSuffix, harmonics, BITS_PER_SAMPLE,
                         Channel::Mono, mp3Data.sampleRate_hz);
  wavEncoder.writeToFile("percussive_" + fileSuffix, percussive,
                         BITS_PER_SAMPLE, Channel::Mono, mp3Data.sampleRate_hz);
  wavEncoder.writeToFile("vocals_" + fileSuffix, vocalsFiltered,
                         BITS_PER_SAMPLE, Channel::Mono, mp3Data.sampleRate_hz);
  LOG_INFO("Done core logic");
}

void createInput(const MP3Data& mp3Data, std::vector<double>& input) {
  switch (mp3Data.channel) {
    case Channel::Mono:
      // Copy mono channel into input vector.
      std::copy(mp3Data.channel1.begin(), mp3Data.channel1.end(),
                input.begin() + PADDING_SIZE);
      break;

    case Channel::Stereo:
      // Take average of both channel to create a mono channel.
      for (size_t n = 0; n < mp3Data.numSamples; n++) {
        input[PADDING_SIZE + n] =
            (mp3Data.channel1[n] + mp3Data.channel2[n]) / 2.0;
      }
      break;

    default:
      LOG_ERROR("Channel type is not supported");
      break;
  }
}
