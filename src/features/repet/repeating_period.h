/**
 *******************************************************************************
 * @file    repeating_period.h
 * @brief   Repeating period header.
 *******************************************************************************
 */

#pragma once

#include <vector>

/**
 * @brief Find the best period from the beat spectrum.
 *
 * @param beatSpectrum Compressed beat spectrum.
 * @return int The best period from the beat spectrum.
 */
int findRepeatingPeriod(std::vector<double>& beatSpectrum);
