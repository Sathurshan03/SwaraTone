/**
 *******************************************************************************
 * @file    lineGraph.cpp
 * @brief   Line Graph source.
 *******************************************************************************
 */

#include "lineGraph.h"

#include <cassert>
#include <iostream>
#include <limits>

#include "constants.h"

LineGraph::LineGraph() {
  chart = new QChart();
  series = new QLineSeries();

  chart->addSeries(series);
  chart->legend()->hide();
  chart->createDefaultAxes();
}

LineGraph::~LineGraph() {
  if (series) {
    chart->removeSeries(series);
    delete series;
  }

  delete chart;
}

void LineGraph::addPoint(double x, double y) { series->append(x, y); }

void LineGraph::addPoints(const std::vector<double>& x,
                          const std::vector<double>& y) {
  assert(x.size() == y.size());

  QVector<QPointF> points;
  points.resize(x.size());

  for (size_t i = 0; i < x.size(); i++) {
    points[i] = QPointF(x[i], y[i]);
  }

  series->replace(points);
}

void LineGraph::setXRange(double lower, double upper) {
  QAbstractAxis* xAxis = chart->axes(Qt::Horizontal).first();
  xAxis->setRange(lower, upper);
}

void LineGraph::setYRange(double lower, double upper) {
  QAbstractAxis* yAxis = chart->axes(Qt::Vertical).first();
  yAxis->setRange(lower, upper);
}

void LineGraph::setTitle(std::string title) {
  chart->setTitle(QString::fromStdString(title));
}

void LineGraph::setXLabel(std::string xLabel) {
  QAbstractAxis* xAxis = chart->axes(Qt::Horizontal).first();
  xAxis->setTitleText(QString::fromStdString(xLabel));
}

void LineGraph::setYLabel(std::string yLabel) {
  QAbstractAxis* yAxis = chart->axes(Qt::Vertical).first();
  yAxis->setTitleText(QString::fromStdString(yLabel));
}

void LineGraph::saveFile(std::string fileName) {
  QSize outputSize(IMG_PIXEL_WIDTH, IMG_PIXEL_HEIGHT);
  chart->resize(outputSize);

  QChartView view(chart);
  view.setRenderHint(QPainter::Antialiasing);
  view.resize(outputSize);

  QPixmap pixmap(outputSize);
  pixmap.fill(Qt::white);
  QPainter painter(&pixmap);

  chart->scene()->render(&painter,
                         QRectF(0, 0, outputSize.width(), outputSize.height()));

  pixmap.save(QString::fromStdString(fileName + ".png"));
}
