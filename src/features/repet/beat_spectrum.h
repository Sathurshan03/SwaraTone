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
