/**
 *******************************************************************************
 * @file    coreLogic.cpp
 * @brief   Core logic source code.
 *******************************************************************************
 */

#include "coreLogic.h"

#include "hpss.h"
#include "matrix.hpp"
#include "mp3.h"


void runCore(std::string filePath) {
  // Read audio input from MP3 file.
  MP3Data mp3Data = readMP3File(filePath);

  // Apply HPSS.
  Matrix harmonics{};
  Matrix percussive{};

  runHPSS(mp3Data.channel1, harmonics, percussive);

  // Reconstruct signal
  // TODO.
}
