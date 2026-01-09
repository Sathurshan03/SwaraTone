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
 * @param W Repeating spectrum.
 * @param V Complex spectrum.
 * @param X STFT of input signal.
 * @return Matrix<std::complex<double>> soft mask on X.
 */
Matrix<std::complex<double>> applySoftMask(
    const Matrix<double>& W, const Matrix<double>& V,
    const Matrix<std::complex<double>>& X);
