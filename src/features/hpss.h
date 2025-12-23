/**
 *******************************************************************************
 * @file    hpss.h
 * @brief   Harmonic Percussice Source Separation (HPSS) header.
 *******************************************************************************
 */

#pragma once

#include <vector>

/**
 * @brief Run HPSS algo.
 *
 * @param[in] in Input signal.
 * @param[in,out] harmonics Harmonic component of input signal.
 * @param[in,out] percussive Percussive component of input signal.
 */
void runHPSS(const std::vector<double>& in, std::vector<double>& harmonics,
             std::vector<double>& percussive);
