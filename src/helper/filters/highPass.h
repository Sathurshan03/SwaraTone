/**
 *******************************************************************************
 * @file    highPass.h
 * @brief   High pass filter header.
 *******************************************************************************
 */

#pragma once

#include <vector>

/**
 * @brief Digital high pass filter. Uses Butterworth degree 2.
 *
 * @param x Input in time domain.
 * @param y Output in time domain.
 * @param fc Frequency cutoff (Hz).
 * @param fs Sample rate (Hz).
 */
void digitalHighPass(const std::vector<double>& x, std::vector<double>& y,
                     double fc, double fs);
