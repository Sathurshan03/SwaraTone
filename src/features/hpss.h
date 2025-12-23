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
 * @param[in,out] harmonics Harmonic component mask.
 * @param[in,out] percussive Percussive component mask.
 */
void runHPSS(std::vector<double>& in, Matrix& mH, Matrix& mP);
