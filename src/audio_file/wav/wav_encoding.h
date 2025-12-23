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
   * @param[in] fileName The name of the file.
   * @param[in] pcm PCM audio data.
   * @param[in] bitsPerSample Bits per sample. (8, 16, 24 or 32).
   * @param[in] channel Mono or stero channel.
   * @param[in] sampleRate The sampling rate.
   */
  void writeToFile(std::string fileName, std::vector<double> pcm,
                   uint16_t bitsPerSample, Channel channel,
                   uint32_t sampleRate);

 private:
  /**
   * @brief Clamps the data within PCM range.
   *
   * @param[in,out] pcm PCM data.
   */
  void clampPCM(std::vector<double>& pcm);

  /**
   * @brief Flush the buffer to the file.
   *
   * @param[in] file File path.
   * @param[in] buffer Buffer to flush.
   * @param[in] numBytesFlush Number of bytes to flush.
   */
  void flushBuffer(std::ofstream& file, char* buffer, size_t& numBytesFlush);

  /**
   * @brief Prepare the WAV header.
   *
   * @param[in] wavHeader The WAV header data struct.
   * @param[in] dataSize The size of the PCM audio data.
   * @param[in] bitsPerSample Bits per sample. (8, 16, 24 or 32).
   * @param[in] channel Mono or stero channel.
   * @param[in] sampleRate The sampling rate.
   */
  void prepareHeader(WavHeaderData& wavHeader, uint32_t dataSize,
                     uint16_t bitsPerSample, Channel channel,
                     uint32_t sampleRate);

  /** @brief Number of bytes per sample. */
  uint16_t bytesPerSample{0};

  /** @brief fmt sub chunk size in little endian representation. */
  uint32_t FMT_SIZE_LE{convertToLE4B(16U)};
};
