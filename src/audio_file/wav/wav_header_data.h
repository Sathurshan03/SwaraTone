/**
 ******************************************************************************
 * @file    wav_header_data.h
 * @brief   WAV file header data struct.
 ******************************************************************************
 */

#pragma once

#include <cstdint>

#pragma pack(1)

/** @brief WAV header data representation. This struct does not hold all
 * parameters as they are constants. */
struct WavHeaderData {
  /** @brief The riff chunk size in number of bytes. */
  uint32_t riffChunkSize;

  /** @brief The data chunk size in number of bytes. */
  uint32_t dataChunkSize;

  /** @brief Audio format. 1 = PCM, 2 = IEEE float. */
  uint16_t audioFormat;

  /** @brief The number of channels. 1 = Mono, 2 = Stereo. */
  uint16_t numChannels;

  /** @brief The sample rate of the audio data. */
  uint32_t sampleRate;

  /** @brief The byte rate per second. (sample rate * bytes per sample). */
  uint32_t byteRate;

  /** @brief Block alignment. (number of channels * bytes per sample). */
  uint16_t blockAlign;

  /** @brief Bits per sample. */
  uint16_t bitsPerSample;
};

#pragma pack()