/**
 *******************************************************************************
 * @file    coreLogic.h
 * @brief   Core logic header.
 *******************************************************************************
 */

#pragma once

#include <string>
#include <vector>

#include "mp3.h"


/**
 * @brief Run core logic.
 *
 * @param filePath Path to mp3 file to run audio decomposition.
 */
void runCore(std::string filePath);

/**
 * @brief Create input based on number of channels for audio processing.
 *
 * @param[in] mp3Data Mp3 input data.
 * @param[out] input Input signal that will be used for audio processing.
 */
void createInput(const MP3Data& mp3Data, std::vector<double>& input);
