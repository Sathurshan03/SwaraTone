/**
 *******************************************************************************
 * @file    hpss.h
 * @brief   Harmonic Percussice Source Separation (HPSS) header.
 *******************************************************************************
 */

#pragma once

#include <vector>

#include "matrix.hpp"

/**
 * @brief Run HPSS algo.
 *
 * @param[in] in Input signal.
 * @param[out] harmonics Harmonic component mask.
 * @param[out] percussive Percussive component mask.
 */
void runHPSS(std::vector<double>& in, Matrix& mH, Matrix& mP);

/**
 * @brief Create a power spectrum time series from input signal.
 *
 * @param[in] in Input signal
 * @param[out] powerSpectrumTs Power spectrum time series of the input.
 */
void createPowerSpectrumTs(std::vector<double>& in, Matrix& powerSpectrumTs);

/**
 * @brief Run median filtering on power spectrum time series.
 *
 * @param[in] powerSpectrumTs Power spectrum time series.
 * @param[out] yH Median filter for harmonics.
 * @param[out] yP Median filter for percussives.
 */
void runMedianFiltering(Matrix& powerSpectrumTs, Matrix& yH, Matrix& yP);
