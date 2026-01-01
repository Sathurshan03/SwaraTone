/**
 *******************************************************************************
 * @file    plot.cpp
 * @brief   Plot source.
 *******************************************************************************
 */

#include "plot.h"

#include <cmath>

#include "constants.h"
#include "heatMapGraph.h"
#include "lineGraph.h"

void plotFrequency(const std::vector<double>& freq,
                   const std::vector<double>& amplitude, bool saveFile,
                   std::string fileName) {
  auto max_it = std::max_element(amplitude.begin(), amplitude.end());

  LineGraph plt;
  plt.addPoints(freq, amplitude);
  plt.setXRange(0, freq.back());
  plt.setYRange(0, *max_it);
  plt.setTitle("Amplitude Vs. Frequency");
  plt.setXLabel("Frequency (Hz)");
  plt.setYLabel("Amplitude");

  if (saveFile) {
    plt.saveFile(fileName);
  }
}

void plotFrequencySpectrogram(const Matrix<std::complex<double>>& spectrogram,
                              bool saveFile, std::string fileName) {
  // Convert the spectrogram amplitude to decibals.
  Matrix<double> data{spectrogram.getNumRows(), spectrogram.getNumCols()};
  const size_t numOps = spectrogram.getNumRows() * spectrogram.getNumCols();

  for (size_t i = 0; i < numOps; i++) {
    double z = 20.0 * std::log10(std::abs(spectrogram(i)) + DOUBLE_EPS);
    data(i) = std::clamp(z, MIN_HUMAN_HEARING_DB, MAX_HUMAN_HEARING_DB);
  }

  // Create the plot.
  HeatMapGraph plt{data, MIN_HUMAN_HEARING_DB, MAX_HUMAN_HEARING_DB};

  if (saveFile) {
    plt.saveFile(fileName);
  }
}