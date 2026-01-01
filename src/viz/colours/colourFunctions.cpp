/**
 *******************************************************************************
 * @file    colourFunctions.cpp
 * @brief   Colour functions source.
 *******************************************************************************
 */

#include "colourFunctions.h"

QRgb linearInterpolateColour(QRgb colourA, QRgb colourB, double alpha) {
  int r =
      static_cast<int>(qRed(colourA) + alpha * (qRed(colourB) - qRed(colourA)));
  int g = static_cast<int>(qGreen(colourA) +
                           alpha * (qGreen(colourB) - qGreen(colourA)));
  int b = static_cast<int>(qBlue(colourA) +
                           alpha * (qBlue(colourB) - qBlue(colourA)));

  r = std::clamp(r, 0, 255);
  g = std::clamp(g, 0, 255);
  b = std::clamp(b, 0, 255);

  return qRgb(r, g, b);
}
