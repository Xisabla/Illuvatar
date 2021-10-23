/*=========================================================================

  Project:   Illuvatar
  File:      wip.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_WIP_H
#define ILLUVATAR_WIP_H

// <--- Temporary stuff that will get included later
/**
 * @enum Alliance
 * @brief Available Alliances between factions
 */
enum Alliance { Evil, Good, NoAlliance };

/**
 * @enum Faction
 * @brief Available Factions in the simulation
 */
enum Faction { Eldars, Valars, Dragons, Werewolves, NoFaction };
// Temporary stuff that will get included later --->

enum Direction { N, NE, E, SE, S, SW, W, NW };

enum ThingOnMap { Void, Nothing, Obstacle, Ennemy, Ally }


#include <map>
#include "geometry/Point.h"

static class Utils {
  public:
    static const std::map<Direction, Point> nextDirection = {
      { Direction::N  : Point( 0, -1) },
      { Direction::NE : Point( 1, -1) },
      { Direction::E  : Point( 1,  0) },
      { Direction::SE : Point( 1,  1) },
      { Direction::S  : Point( 0,  1) },
      { Direction::SW : Point(-1,  1) },
      { Direction::W  : Point(-1,  0) },
      { Direction::NW : Point(-1, -1) }
    }
    static const std::map<pair<int, int>, Direction> deltaDirection = {
      { { 0, -1} :  Direction::N  },
      { { 1, -1} :  Direction::NE },
      { { 1,  0} :  Direction::E  },
      { { 1,  1} :  Direction::SE },
      { { 0,  1} :  Direction::S  },
      { {-1,  1} :  Direction::SW },
      { {-1,  0} :  Direction::W  },
      { {-1, -1} :  Direction::NW }
    }
}

#endif // ILLUVATAR_WIP_H
