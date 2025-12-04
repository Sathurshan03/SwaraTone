/**
 *******************************************************************************
 * @file    windowing_functions.h
 * @brief   Windowing functions header.
 *******************************************************************************
 */

#pragma once

/**
 * @brief Apply Haning Windowing function to input signal.
 *
 * @param x Input signal.
 * @param N Size of input signal.
 */
void applyHanningWindow(double* x, int N);
