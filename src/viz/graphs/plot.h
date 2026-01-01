/**
 *******************************************************************************
 * @file    plot.h
 * @brief   Plot header.
 *******************************************************************************
 */

#pragma once

#include <complex>
#include <string>
#include <vector>

#include "matrix.hpp"

/**
 * @brief Creates a frequency plot.
 *
 * @param freq Frequency (x axis).
 * @param amplitude frequency amplitude (y axis).
 * @param saveFile True to save the plot to a file.
 * @param fileName The file name given @ref saveFile is true.
 */
void plotFrequency(const std::vector<double>& freq,
                   const std::vector<double>& amplitude, bool saveFile = false,
                   std::string fileName = "freqPlot");

/**
 * @brief Creates a spectrogram plot.
 *
 * @param spectrogram Frequency spectrogram.
 * @param saveFile True to save the plot to a file.
 * @param fileName The file name given @ref saveFile is true.
 */
void plotFrequencySpectrogram(const Matrix<std::complex<double>>& spectrogram,
                              bool saveFile = false,
                              std::string fileName = "spectrogramPlot");
