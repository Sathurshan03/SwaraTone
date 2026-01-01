/**
 *******************************************************************************
 * @file    heatMapGraph.cpp
 * @brief   Heat map graph source.
 *******************************************************************************
 */

#include "heatMapGraph.h"

#include <QPainter>
#include <QRect>
#include <QTransform>
#include <cassert>
#include <cmath>

#include "colourFunctions.h"
#include "constants.h"
#include "plasmaColourMap.h"

HeatMapGraph::HeatMapGraph(const Matrix<double>& data, double minVal,
                           double maxVal)
    : minVal(minVal), maxVal(maxVal) {
  assert(this->minVal != this->maxVal);

  imgSize = QSize(data.getNumRows(), data.getNumCols());
  img = QImage(imgSize, QImage::Format_RGB32);
  img.fill(Qt::white);

  fillHeatValues(data);
}

void HeatMapGraph::rotateClockWise() {
  QTransform transform;
  transform.rotate(90.0);
  img = img.transformed(transform);
}

void HeatMapGraph::rotateCounterClockWise() {
  QTransform transform;
  transform.rotate(-90.0);
  img = img.transformed(transform);
}

void HeatMapGraph::saveFile(std::string fileName) {
  QPixmap pixmap(imgSize);
  pixmap.fill(Qt::white);
  QPainter painter(&pixmap);

  painter.setRenderHint(QPainter::LosslessImageRendering, true);
  QPoint topleft{0, 0};
  painter.drawImage(QRect(0, 0, imgSize.width(), imgSize.height()), img);

  pixmap.save(QString::fromStdString(fileName + ".png"));
}

void HeatMapGraph::fillHeatValues(const Matrix<double>& data) {
  double range = maxVal - minVal;
  double multiplier = static_cast<double>(PLASMA_LUT_SIZE) / range;
  const int maxIdx = PLASMA_LUT_SIZE - 1;
  QRgb colour;

  for (size_t x = 0; x < data.getNumRows(); x++) {
    for (size_t y = 0; y < data.getNumCols(); y++) {
      double per = (data(x, y) - minVal) / range;
      double fidx = per * maxIdx;

      int idxColourA = static_cast<int>(std::floor(fidx));
      int idxColourB = idxColourA + 1;

      idxColourA = std::clamp(idxColourA, 0, maxIdx);
      idxColourB = std::clamp(idxColourB, 0, maxIdx);
      double alpha = fidx - idxColourA;

      colour = linearInterpolateColour(PLASMA_LUT[idxColourA],
                                       PLASMA_LUT[idxColourB], alpha);

      img.setPixel(x, imgSize.height() - y - 1, colour);
    }
  }
}
