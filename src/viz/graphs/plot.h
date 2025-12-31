/**
 *******************************************************************************
 * @file    plot.h
 * @brief   Plot header.
 *******************************************************************************
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Creates a frequency plot.
 *
 * @param freq Frequency (x axis).
 * @param amplitude frequency amplitude (y axis).
 * @param saveFile True to save the plot to a file.
 * @param fileName The file name given @ref saveFile is true.
 */
void plotFrequency(std::vector<double> freq, std::vector<double> amplitude,
                   bool saveFile = false, std::string fileName = "freqPlt");
