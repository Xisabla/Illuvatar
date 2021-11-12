/*=========================================================================

Project:   Illuvatar
File:      Faction.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DIRECTION_H
#define ILLUVATAR_DIRECTION_H

#include <iostream>
#include <string>
#include <map>

#define DIRECTION_FIRST N
#define DIRECTION_LAST NW

/**
 * @enum Direction
 * @brief Cardinal directions in the map
 */
enum class Direction { DIRECTION_FIRST, NE, E, SE, S, SW, W, DIRECTION_LAST };

std::ostream& operator<<(std::ostream& out, Direction value);

/**
 * @brief Transform a Direction into a string
 */
const std::map<Direction, std::string> strFromDirection = {
    { Direction::N, "N" },
    { Direction::NE, "NE" },
    { Direction::E, "E" },
    { Direction::SE, "SE" },
    { Direction::S, "S" },
    { Direction::SW, "SW" },
    { Direction::W, "W" },
    { Direction::NW, "NW" }
};

#endif // ILLUVATAR_DIRECTION_H
