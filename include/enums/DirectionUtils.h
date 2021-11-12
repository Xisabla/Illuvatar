/*=========================================================================

  Project:   Illuvatar
  File:      DirectionUtils.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DirectionUtils_H
#define ILLUVATAR_DirectionUtils_H

#include "enums/Direction.h"
#include "superTypes.h"
#include "unirand.h"

#include <iostream>
#include <map>
#include <vector>

namespace directionutils { 
/**
 * @brief Transform a direction into a list of "continuous" directions (same and diagonals)
 */
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

/**
 * @brief Transform a direction into a list of "sides" directions (sides and opposite diagonals)
 */
const std::map<Direction, std::vector<Direction>> sideDirections = {
    { Direction::N, { Direction::E, Direction::SE, Direction::SW, Direction::W } },
    { Direction::NE, { Direction::SE, Direction::S, Direction::W, Direction::NW } },
    { Direction::E, { Direction::S, Direction::SW, Direction::NW, Direction::N } },
    { Direction::SE, { Direction::SW, Direction::W, Direction::N, Direction::NE } },
    { Direction::S, { Direction::W, Direction::NW, Direction::NE, Direction::E } },
    { Direction::SW, { Direction::NW, Direction::N, Direction::E, Direction::SE } },
    { Direction::W, { Direction::N, Direction::NE, Direction::SE, Direction::S } },
    { Direction::NW, { Direction::NE, Direction::E, Direction::S, Direction::SW } }
};

/**
 * @brief Transform a direction into its opposite direction
 */
const std::map<Direction, Direction> oppositeDirection = {
    { Direction::N, Direction::S }, { Direction::NE, Direction::SW },
    { Direction::E, Direction::W }, { Direction::SE, Direction::NW },
    { Direction::S, Direction::N }, { Direction::SW, Direction::NE },
    { Direction::W, Direction::E }, { Direction::NW, Direction::SE }
};

/**
 * @brief Transform a direction into a variation of coordinates
 */
const std::map<Direction, superTypes::Point> nextDirection = {
    { Direction::N, {0, -1} }, { Direction::NE, {1, -1} },
    { Direction::E, {1, 0} },  { Direction::SE, {1, 1} },
    { Direction::S, {0, 1} },  { Direction::SW, {-1, 1} },
    { Direction::W, {-1, 0} }, { Direction::NW, {-1, -1} }
};

/**
 * @brief Transform a variation of coordinates into a direction
 */
const std::map<std::pair<int, int>, Direction> deltaDirection = {
    { { 0, -1 }, Direction::N }, { { 1, -1 }, Direction::NE }, { { 1, 0 }, Direction::E },
    { { 1, 1 }, Direction::SE }, { { 0, 1 }, Direction::S },   { { -1, 1 }, Direction::SW },
    { { -1, 0 }, Direction::W }, { { -1, -1 }, Direction::NW }
};

/**
 * Compute the direction of the vector composed by two neighboring points
 * @param last The origin of the vector
 * @param current the arrival of the vector
 * @return The direction of the vector
 */
Direction computeDirection(const superTypes::Point& last, const superTypes::Point& current);

/**
 * Compute the reverse variation of coordinates corresponding to the direction
 * @param direction The direction of the vector
 * @return The variation to the origin of the vector
 */
superTypes::Point computeLastJump(const Direction& direction);

/**
 * @return An uniform random based Direction
 */
Direction randDirection();
} // namespace directionutils

#endif // ILLUVATAR_DirectionUtils_H
