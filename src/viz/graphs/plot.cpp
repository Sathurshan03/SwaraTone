/**
 *******************************************************************************
 * @file    plot.cpp
 * @brief   Plot source.
 *******************************************************************************
 */

#include "plot.h"

#include "lineGraph.h"

void plotFrequency(std::vector<double> freq, std::vector<double> amplitude,
                   bool saveFile, std::string fileName) {
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
