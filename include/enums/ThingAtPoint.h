/*=========================================================================

Project:   Illuvatar
File:      ThingAtPoint.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_THINGATPOINT_H
#define ILLUVATAR_THINGATPOINT_H

#include <iostream>

/**
 * @enum ThingAtPoint
 * @brief Objects that can be found on tile - or no tile at all
 */
enum class ThingAtPoint { Void, Nothing, Obstacle, Character, Ennemy, Ally };

std::ostream& operator<<(std::ostream& out, const ThingAtPoint value);

#endif // ILLUVATAR_THINGATPOINT_H
