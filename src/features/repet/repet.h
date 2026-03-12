/**
 *******************************************************************************
 * @file    repet.h
 * @brief   REpeating Pattern Extraction Technique (REPET) header file.
 *******************************************************************************
 */

#pragma once

// TODO: instead of return, pass as input.
Matrix<std::complex<double>> runRepet(const Matrix<double>& magnitudeSpectrum,
                                      const Matrix<double>& powerSpectrum,
                                      const Matrix<std::complex<double>>& X);
