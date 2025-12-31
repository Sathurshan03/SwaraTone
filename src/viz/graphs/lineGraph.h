/**
 *******************************************************************************
 * @file    lineGraph.h
 * @brief   Line Graph header.
 *******************************************************************************
 */

#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <string>
#include <vector>

/** @brief Class for handling line graphing using Qt. */
class LineGraph {
 public:
  /** @brief Construct a new Line Graph object. */
  LineGraph();

  /** @brief Destroy the Line Graph object. */
  ~LineGraph();

  /**
   * @brief Adds a point to the graph.
   *
   * @param x X component.
   * @param y Y component.
   */
  void addPoint(double x, double y);

  /**
   * @brief Adds several points to the graph.
   *
   * @param x Vector of x components.
   * @param y Vector of y components corresponding to @ref x.
   */
  void addPoints(const std::vector<double>& x, const std::vector<double>& y);

  /**
   * @brief Set the range forthe X axis.
   *
   * @param lower The lower bound of the range.
   * @param upper The upper bound o the range.
   */
  void setXRange(double lower, double upper);

  /**
   * @brief Set the range forthe Y axis.
   *
   * @param lower The lower bound of the range.
   * @param upper The upper bound o the range.
   */
  void setYRange(double lower, double upper);

  /** @brief Set the title for the graph. */
  void setTitle(std::string title);

  /** @brief Set the x label. */
  void setXLabel(std::string xLabel);

  /** @brief Set the y label. */
  void setYLabel(std::string yLabel);

  /**
   * @brief Save the graph into a file.
   *
   * @param fileName The name of the file without the file extension.
   */
  void saveFile(std::string fileName);

 private:
  /** @brief Qt series holding graph data. */
  QLineSeries* series;

  /** @brief Qt chart object. This holds the Qt series and addition plot info
   * such as title, labels, etc. */
  QChart* chart;
};
