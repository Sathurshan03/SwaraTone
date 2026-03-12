/**
 *******************************************************************************
 * @file    beat_spectrum.h
 * @brief   Beat spectrum header.
 *******************************************************************************
 */

#pragma once

#include <vector>

#include "matrix.hpp"

/**
 * @brief Creates a condensed beat spectrum from the power spectrum.
 *
 * @param[in] powerSpectrum Power spectrum
 * @return std::vector<double> Condensed beat spectrum.
 */
std::vector<double> createBeatSpectrum(const Matrix<double>& powerSpectrum);

/**
 * @brief Thread for computing a row in the beat spectrum.
 *
 * @param lag The lag number
 * @param numTimeFrames The total number of time frames.
 * @param numFreq The total number of frequency bins.
 * @param[in] powerSpectrum Power spectrum.
 * @param[in,out] beatSpectrum Beat spectrum
 */
void computeBeatSpectrumThread(size_t lag, size_t numTimeFrames, size_t numFreq,
                               const Matrix<double>& powerSpectrum,
                               std::vector<double>& beatSpectrum);
