/**
 *******************************************************************************
 * @file    heatMapGraph.h
 * @brief   Heat map graph header.
 *******************************************************************************
 */

#pragma once

#include <QImage>
#include <string>

#include "matrix.hpp"

/** @brief Class for handling heat map graphing using Qt. */
class HeatMapGraph {
 public:
  /**
   * @brief Construct a new Heat Map Graph object.
   *
   * @param[in] data Matrix data.
   * @param minVal Min value from @ref data.
   * @param maxVal Max value from @ref data.
   */
  HeatMapGraph(const Matrix<double>& data, double minVal, double maxVal);

  /** @brief Rotates the graph image by 90 degrees clockwise.*/
  void rotateClockWise();

  /** @brief Rotates the graph image by 90 degrees counter clockwise.*/
  void rotateCounterClockWise();

  /**
   * @brief Save the graph into a file.
   *
   * @param fileName The name of the file without the file extension.
   */
  void saveFile(std::string fileName);

 private:
  /**
   * @brief Fill in the image with corresponding heat values.
   *
   * @param[in] data Matrix data.
   */
  void fillHeatValues(const Matrix<double>& data);

  /** @brief Min value of heat map values. */
  double minVal;

  /** @brief Max value of heat map values. */
  double maxVal;

  /** @brief Image holding heat map graph. */
  QImage img;

  /** @brief Size of @ref img in pixels. */
  QSize imgSize;
};