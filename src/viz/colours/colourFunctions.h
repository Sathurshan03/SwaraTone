/**
 *******************************************************************************
 * @file    colourFunctions.h
 * @brief   Colour functions header.
 *******************************************************************************
 */

#pragma once

#include <QColor>

/**
 * @brief Linear interpolated between two colours.
 *
 * @param colourA Colour A. Colour A RGB is less than @ref colourB on some
 * colour map.
 * @param colourB Colour B.
 * @param alpha Percent distance from @ref colourA. Denominator is the distance
 * between @ref colourA and @ref colourB.
 * @return QRgb Interpolated colour..
 */
QRgb linearInterpolateColour(QRgb colourA, QRgb colourB, double alpha);
