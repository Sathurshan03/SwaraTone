/**
 *******************************************************************************
 * @file    beat_soft_mask.h
 * @brief   Beat soft mask header.
 *******************************************************************************
 */

#pragma once

#include <complex>

#include "matrix.hpp"

/**
 * @brief Applies soft mask onto STFT X
 *
 * @param repeatWeight Repeating weight spectrum.
 * @param totalEnergyMatrix Complex spectrum.
 * @param X STFT of input signal.
 * @return Matrix<std::complex<double>> soft mask on X.
 */
Matrix<std::complex<double>> applySoftMask(
    const Matrix<double>& repeatWeight, const Matrix<double>& totalEnergyMatrix,
    const Matrix<std::complex<double>>& X);
