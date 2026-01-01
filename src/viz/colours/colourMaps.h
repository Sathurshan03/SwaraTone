/**
 *******************************************************************************
 * @file    colourMaps.h
 * @brief   Colour maps header.
 *******************************************************************************
 */

#pragma once

#include <array>

#include "magmaColourMap.h"
#include "plasmaColourMap.h"

struct ColourMap {
  /** @brief Address of look up table for colour map. */
  const QRgb* LUT;

  /** @brief Size of the the colour map's look up table. */
  int size;
};

// Colour maps.
inline constexpr ColourMap PLASMA_COLOUR_MAP{PLASMA_LUT, PLASMA_LUT_SIZE};
inline constexpr ColourMap MAGMA_COLOUR_MAP{MAGMA_LUT, MAGMA_LUT_SIZE};

// Colour map array.
inline constexpr std::array<ColourMap, 2> COLOUR_MAPS = {PLASMA_COLOUR_MAP,
                                                         MAGMA_COLOUR_MAP};

/** @brief Enum holding colour maps. Order corresponds to @ref COLOUR_MAPS */
enum ColourMapID { PLASMA, MAGMA };
