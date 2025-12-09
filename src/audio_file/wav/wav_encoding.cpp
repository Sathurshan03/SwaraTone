/**
 ******************************************************************************
 * @file    wav_encoding.cpp
 * @brief   WAV file encoding source code.
 ******************************************************************************
 */
#include "wav_encoding.h"

#include <algorithm>
#include <fstream>

#include "constants.h"
#include "endian.h"
#include "logging.h"

WAVFileEncoder::WAVFileEncoder() {};

void WAVFileEncoder::writeToFile(std::string fileName, std::vector<double> pcm,
                                 uint16_t bitsPerSample, Channel channel,
                                 uint32_t sampleRate) {
  // TODO: Restrict bits per sample is 8, 16, 24 or 32.

  // Prepare WAV header data.
  WavHeaderData wavHeader{};
  this->prepareHeader(wavHeader, static_cast<uint32_t>(pcm.size()),
                      bitsPerSample, channel, sampleRate);

  // TODO: Move the file reader to another file or class in helper.
  // Stream WAV header data to file.
  std::string path = fileName + ".wav";
  std::ofstream wavFile(path, std::ios::out | std::ios::binary);
  if (!wavFile.is_open()) {
    LOG_ERROR("Error in opening file: " << path);
    return;
  }

  char wavHeaderChar[44];
  size_t offset = 0;

  // RIFF chunk.
  memcpy(wavHeaderChar + offset, "RIFF", 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, &wavHeader.riffChunkSize, 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, "WAVE", 4);
  offset += 4;

  // fmt sub chunk.
  memcpy(wavHeaderChar + offset, "fmt ", 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, &FMT_SIZE_LE, 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, &wavHeader.audioFormat, 2);
  offset += 2;

  memcpy(wavHeaderChar + offset, &wavHeader.numChannels, 2);
  offset += 2;

  memcpy(wavHeaderChar + offset, &wavHeader.sampleRate, 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, &wavHeader.byteRate, 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, &wavHeader.blockAlign, 2);
  offset += 2;

  memcpy(wavHeaderChar + offset, &wavHeader.bitsPerSample, 2);
  offset += 2;

  memcpy(wavHeaderChar + offset, "data", 4);
  offset += 4;

  memcpy(wavHeaderChar + offset, &wavHeader.dataChunkSize, 4);
  offset += 4;

  wavFile.write(wavHeaderChar, sizeof(wavHeaderChar));

  // Stream audio data to WAV file.
  // TODO: clean up and throw into their own functions.
  if (bitsPerSample == 8) {
    char buffer[1024];
    size_t bufferSize = sizeof(buffer);
    offset = 0;

    for (double sample : pcm) {
      if (offset >= bufferSize) {
        wavFile.write(buffer, offset);
        offset = 0;
      }

      if (sample > 1.0) {
        sample = 1.0;
      } else if (sample < -1.0) {
        sample = -1.0;
      }

      uint8_t pcmUInt = static_cast<uint8_t>(sample * INT8_MAX);
      memcpy(buffer + offset, &pcmUInt, 1);
      offset += 1;
    }

    // TODO: this flush can be its own function.
    if (offset >= bufferSize) {
      wavFile.write(buffer, offset);
    }
  }

  else if (bitsPerSample == 16) {
    // TODO: remember LE.
  }

  else if (bitsPerSample == 24) {
    // TODO: remember LE.
    // Lets skip this for now.
  }

  else if (bitsPerSample == 32) {
    // TODO: remember LE.
  }

  wavFile.close();
}

void WAVFileEncoder::prepareHeader(WavHeaderData& wavHeader, uint32_t dataSize,
                                   uint16_t bitsPerSample, Channel channel,
                                   uint32_t sampleRate) {
  // Store the data in little endian format as WAV data can only be in that
  // format.

  this->bytesPerSample = bitsPerSample / static_cast<uint16_t>(BYTE_SIZE);
  uint16_t blockAlign = wavHeader.numChannels * bytesPerSample;
  uint32_t dataChunkSize = dataSize * blockAlign;

  // Add 36 to include contents of WAV  header except for RIFF chunk desciption.
  wavHeader.riffChunkSize = endianSwap4B(dataChunkSize + 36U);
  wavHeader.dataChunkSize = endianSwap4B(dataChunkSize);
  wavHeader.audioFormat = endianSwap2B(1U);
  wavHeader.numChannels = endianSwap2B(static_cast<uint16_t>(channel));
  wavHeader.sampleRate = endianSwap4B(sampleRate);
  wavHeader.byteRate = endianSwap4B(sampleRate * wavHeader.blockAlign);
  wavHeader.blockAlign = endianSwap2B(blockAlign);
  wavHeader.bitsPerSample = endianSwap2B(bitsPerSample);
}