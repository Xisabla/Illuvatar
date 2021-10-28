/*=========================================================================

  Project:   Illuvatar
  File:      DirectionUtils.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DirectionUtils_H
#define ILLUVATAR_DirectionUtils_H

#include "geometry/Point.h"
#include "map/Tile.h"

#include <map>
#include <vector>

#define DIRECTION_FIRST N
#define DIRECTION_LAST NW

namespace directionutils {
enum class Direction { DIRECTION_FIRST, NE, E, SE, S, SW, W, DIRECTION_LAST };

const std::map<Direction, std::vector<Direction>> fanDirections = {
    { Direction::N, { Direction::NW, Direction::N, Direction::NE } },
    { Direction::NE, { Direction::N, Direction::NE, Direction::E } },
    { Direction::E, { Direction::NE, Direction::E, Direction::SE } },
    { Direction::SE, { Direction::E, Direction::SE, Direction::S } },
    { Direction::S, { Direction::SE, Direction::S, Direction::SW } },
    { Direction::SW, { Direction::S, Direction::SW, Direction::W } },
    { Direction::W, { Direction::SW, Direction::W, Direction::NW } },
    { Direction::NW, { Direction::W, Direction::NW, Direction::N } }
};
const std::map<Direction, Direction> oppositeDirection = {
    { Direction::N, Direction::S }, { Direction::NE, Direction::SW },
    { Direction::E, Direction::W }, { Direction::SE, Direction::NW },
    { Direction::S, Direction::N }, { Direction::SW, Direction::NE },
    { Direction::W, Direction::E }, { Direction::NW, Direction::SE }
};

const std::map<Direction, Point> nextDirection = {
    { Direction::N, Point(0, -1) }, { Direction::NE, Point(1, -1) },
    { Direction::E, Point(1, 0) },  { Direction::SE, Point(1, 1) },
    { Direction::S, Point(0, 1) },  { Direction::SW, Point(-1, 1) },
    { Direction::W, Point(-1, 0) }, { Direction::NW, Point(-1, -1) }
};
const std::map<std::pair<int, int>, Direction> deltaDirection = {
    { { 0, -1 }, Direction::N }, { { 1, -1 }, Direction::NE }, { { 1, 0 }, Direction::E },
    { { 1, 1 }, Direction::SE }, { { 0, 1 }, Direction::S },   { { -1, 1 }, Direction::SW },
    { { -1, 0 }, Direction::W }, { { -1, -1 }, Direction::NW }
};

Direction computeDirection(const Tile &last, const Tile &current);
}; // namespace directionutils

#endif // ILLUVATAR_DirectionUtils_H
