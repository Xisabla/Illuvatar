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

#define DIRECTION_FIRST N
#define DIRECTION_LAST NW

/**
 * @enum Direction
 * @brief Cardinal directions in the map
 */
enum class Direction { DIRECTION_FIRST, NE, E, SE, S, SW, W, DIRECTION_LAST };

std::ostream& operator<<(std::ostream& out, Direction value);

#endif // ILLUVATAR_DIRECTION_H
