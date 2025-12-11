/**
 ******************************************************************************
 * @file    wav_encoding.h
 * @brief   WAV file encoding header.
 ******************************************************************************
 */

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "channel.h"
#include "endian.h"
#include "wav_header_data.h"

/** @brief Audio encoder to WAV file. */
class WAVFileEncoder {
 public:
  /** @brief Construct a new WAVFileEncoder object. */
  WAVFileEncoder();

  /**
   * @brief Write to WAV file.
   *
   * @param fileName The name of the file.
   * @param pcm PCM audio data.
   * @param bitsPerSample Bits per sample. (8, 16, 24 or 32).
   * @param channel Mono or stero channel.
   * @param sampleRate The sampling rate.
   */
  void writeToFile(std::string fileName, std::vector<double> pcm,
                   uint16_t bitsPerSample, Channel channel,
                   uint32_t sampleRate);

 private:
  void clampPCM(std::vector<double>& pcm);

  void flushBuffer(std::ofstream& file, char* buffer, size_t& numBytesFlush);

  /**
   * @brief Prepare the WAV header.
   *
   * @param wavHeader The WAV header data struct.
   * @param dataSize The size of the PCM audio data.
   * @param bitsPerSample Bits per sample. (8, 16, 24 or 32).
   * @param channel Mono or stero channel.
   * @param sampleRate The sampling rate.
   */
  void prepareHeader(WavHeaderData& wavHeader, uint32_t dataSize,
                     uint16_t bitsPerSample, Channel channel,
                     uint32_t sampleRate);

  /** @brief Number of bytes per sample. */
  uint16_t bytesPerSample{0};

  /** @brief fmt sub chunk size in little endian representation. */
  uint32_t FMT_SIZE_LE{convertToLE4B(16U)};
};
