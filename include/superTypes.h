/*=========================================================================

  Project:   Illuvatar
  File:      superTypes.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_SUPERTYPES_H
#define ILLUVATAR_SUPERTYPES_H

#include "enums/Direction.h"

#include <vector>

namespace superTypes {


typedef std::pair<int, int> Point;

/**
 * @brief A vector of Point
 */
typedef std::vector<Point> Path;

/**
 * @brief A vector of pair of Point and Direction
 */
typedef std::vector<std::pair<Point, Direction>> DirectionalPath;
}

#endif // ILLUVATAR_SUPERTYPES_H
