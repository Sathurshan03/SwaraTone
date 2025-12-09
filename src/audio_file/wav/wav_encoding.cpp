/**
 ******************************************************************************
 * @file    wav_encoding.cpp
 * @brief   WAV file encoding source code.
 ******************************************************************************
 */

#include "wav_encoding.h"

#include <algorithm>

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

  size_t wavHeaderSize = sizeof(wavHeaderChar);
  this->flushBuffer(wavFile, wavHeaderChar, wavHeaderSize);

  // Stream audio data to WAV file.
  this->clampPCM(pcm);

  char buffer[1024];
  size_t bufferSize = sizeof(buffer);
  offset = 0;

  if (bitsPerSample == 8) {
    for (double sample : pcm) {
      if (offset >= bufferSize) {
        this->flushBuffer(wavFile, buffer, offset);
      }

      uint8_t pcmUInt = static_cast<uint8_t>(sample * INT8_MAX);
      memcpy(buffer + offset, &pcmUInt, 1);
      offset += 1;
    }

    this->flushBuffer(wavFile, buffer, offset);
  }

  else if (bitsPerSample == 16) {
    for (double sample : pcm) {
      if (offset >= bufferSize) {
        this->flushBuffer(wavFile, buffer, offset);
      }

      uint16_t pcmUInt = static_cast<uint16_t>(sample * INT16_MAX);
      pcmUInt = convertToLE2B(pcmUInt);
      memcpy(buffer + offset, &pcmUInt, 2);
      offset += 2;
    }

    this->flushBuffer(wavFile, buffer, offset);
  }

  else if (bitsPerSample == 24) {
    LOG_ERROR("24 bits per sample is currently not supported.");
  }

  else if (bitsPerSample == 32) {
    for (double sample : pcm) {
      if (offset >= bufferSize) {
        this->flushBuffer(wavFile, buffer, offset);
      }

      uint32_t pcmUInt = static_cast<uint32_t>(sample * INT32_MAX);
      pcmUInt = convertToLE4B(pcmUInt);
      memcpy(buffer + offset, &pcmUInt, 4);
      offset += 4;
    }

    this->flushBuffer(wavFile, buffer, offset);
  }

  wavFile.close();
}

void WAVFileEncoder::clampPCM(std::vector<double>& pcm) {
  for (double& data : pcm) {
    data = std::clamp(data, -1.0, 1.0);
  }
}

void WAVFileEncoder::flushBuffer(std::ofstream& file, char* buffer,
                                 size_t& numBytesFlush) {
  if (numBytesFlush > 0) {
    file.write(buffer, numBytesFlush);
    numBytesFlush = 0;
  }
}

void WAVFileEncoder::prepareHeader(WavHeaderData& wavHeader, uint32_t dataSize,
                                   uint16_t bitsPerSample, Channel channel,
                                   uint32_t sampleRate) {
  // Store the data in little endian format as WAV data can only be in that
  // format.

  this->bytesPerSample = bitsPerSample / static_cast<uint16_t>(BYTE_SIZE);
  uint16_t numChannels = static_cast<uint16_t>(channel);
  uint16_t blockAlign = numChannels * bytesPerSample;
  uint32_t dataChunkSize = dataSize * blockAlign;

  // Add 36 to include contents of WAV  header except for RIFF chunk desciption.
  wavHeader.riffChunkSize = convertToLE4B(dataChunkSize + 36U);
  wavHeader.dataChunkSize = convertToLE4B(dataChunkSize);
  wavHeader.audioFormat = convertToLE2B(1U);
  wavHeader.numChannels = convertToLE2B(numChannels);
  wavHeader.sampleRate = convertToLE4B(sampleRate);
  wavHeader.byteRate = convertToLE4B(sampleRate * wavHeader.blockAlign);
  wavHeader.blockAlign = convertToLE2B(blockAlign);
  wavHeader.bitsPerSample = convertToLE2B(bitsPerSample);
}
