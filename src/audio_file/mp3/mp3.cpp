/**
 ******************************************************************************
 * @file    mp3.cpp
 * @brief   MP3 processing functions.
 ******************************************************************************
 */

#define MINIMP3_IMPLEMENTATION

#include "mp3.h"

#include <stdio.h>

#include <algorithm>
#include <fstream>

#include "logging.h"

MP3Data readMP3File(std::string filepath) {
  std::vector<unsigned char> rawMp3Data = readRawMP3(filepath);

  // Decode MP3 bnary to Pulse Code Modulation (PCM).
  // PCM allows to represent analog signals digitally.
  mp3dec_t dec;
  mp3dec_file_info_t info;  // PCM will be stored here

  mp3dec_init(&dec);
  int statusCode = mp3dec_load_buf(&dec, rawMp3Data.data(), rawMp3Data.size(),
                                   &info, nullptr, nullptr);

  if (statusCode != 0) {
    LOG_ERROR("Error in decoding MP3 binary data.");
  }

  LOG_INFO("Decoded # samples: " << info.samples);
  LOG_INFO("Sample rate (Hz): " << info.hz);
  LOG_INFO("Channels: " << info.channels);

  // Process data based on channel type.
  Channel channel = static_cast<Channel>(info.channels);
  MP3Data data;

  if (channel == Channel::Mono) {
    data = handleMonoChannel(info);

  } else if (channel == Channel::Stereo) {
    data = handleStereoChannel(info);
  }

  return data;
}

std::vector<unsigned char> readRawMP3(std::string filepath) {
  // Open the file in binary mode.
  std::ifstream file(filepath, std::ios::binary);

  if (!file) {
    LOG_ERROR("Could not find file " << filepath.c_str());
  } else if (!file.is_open()) {
    LOG_ERROR("Could not open file " << filepath.c_str());
  }

  // Determine the file size.
  file.seekg(0, file.end);
  int fileSize = static_cast<int>(file.tellg());
  file.seekg(0, file.beg);

  // Store raw binary to a vector.
  std::vector<char> signedRawMp3Data(fileSize);
  std::vector<unsigned char> rawMp3Data(fileSize);

  file.read(signedRawMp3Data.data(), fileSize);
  file.close();

  std::transform(signedRawMp3Data.begin(), signedRawMp3Data.end(),
                 rawMp3Data.begin(),
                 [](char c) { return static_cast<unsigned char>(c); });

  return rawMp3Data;
}

MP3Data handleMonoChannel(mp3dec_file_info_t& info) {
  LOG_INFO("Mono Channel.");

  // Normalize and store MP3 data into a vector.
  std::vector<double> normalizedPcm(info.samples);
  for (size_t i = 0; i < info.samples; i++) {
    normalizedPcm[i] = static_cast<double>(info.buffer[i]) / INT16_MAX;
  }

  MP3Data data = {info.samples, Channel::Mono, normalizedPcm, {}};
  return data;
}

MP3Data handleStereoChannel(mp3dec_file_info_t& info) {
  LOG_INFO("Stereo Channel");

  size_t numSamples = info.samples / 2;
  std::vector<double> normalizedLeftPcm(numSamples);
  std::vector<double> normalizedRightPcm(numSamples);

  // Processing intertwining channel sample, normalizing, and store MP3 data
  // into vector.
  for (size_t i = 0; i < numSamples; i++) {
    normalizedLeftPcm[i] = static_cast<double>(info.buffer[2 * i]) / INT16_MAX;
    normalizedRightPcm[i] =
        static_cast<double>(info.buffer[2 * i + 1]) / INT16_MAX;
  }

  MP3Data data = {info.samples, Channel::Stereo, normalizedLeftPcm,
                  normalizedRightPcm};
  return data;
}
