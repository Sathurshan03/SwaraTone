/**
 *******************************************************************************
 * @file    heatMapGraph.cpp
 * @brief   Heat map graph source.
 *******************************************************************************
 */

#include "heatMapGraph.h"

#include <QPainter>
#include <QRect>
#include <cassert>
#include <cmath>

#include "constants.h"
#include "plasmaColourMap.h"

HeatMapGraph::HeatMapGraph(const Matrix<double>& data, double minVal,
                           double maxVal) {
  this->minVal = static_cast<int>(std::floor(minVal));
  this->maxVal = static_cast<int>(std::ceil(maxVal));
  assert(this->minVal != this->maxVal);

  imgSize = QSize(data.getNumRows(), data.getNumCols());
  img = QImage(imgSize, QImage::Format_RGB32);
  img.fill(Qt::white);

  fillHeatValues(data);
}

void HeatMapGraph::saveFile(std::string fileName) {
  QPixmap pixmap(imgSize);
  pixmap.fill(Qt::white);
  QPainter painter(&pixmap);

  painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
  QPoint topleft{0, 0};
  painter.drawImage(QRect(0, 0, imgSize.width(), imgSize.height()), img);

  int scaleFactor = std::min(IMG_PIXEL_WIDTH / imgSize.width(),
                             IMG_PIXEL_HEIGHT / imgSize.height());

  imgSize *= scaleFactor;
  img = img.scaled(imgSize);

  pixmap.save(QString::fromStdString(fileName + ".png"));
}

void HeatMapGraph::fillHeatValues(const Matrix<double>& data) {
  int range = maxVal - minVal;
  double multiplier = static_cast<double>(PLASMA_LUT_SIZE) / range;

  for (size_t x = 0; x < data.getNumRows(); x++) {
    for (size_t y = 0; y < data.getNumCols(); y++) {
      int idx = static_cast<int>((data(x, y) - minVal) * multiplier);
      idx = std::clamp(idx, 0, PLASMA_LUT_SIZE - 1);
      img.setPixel(x, imgSize.height() - y - 1, PLASMA_LUT[idx]);
    }
  }
}
