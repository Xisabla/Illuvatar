/*=========================================================================

  Project:   Illuvatar
  File:      Tile.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_PathFinder_H
#define ILLUVATAR_PathFinder_H

#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include "map/Tile.h"
#include "map/Map.h"
#include "wip.h"

/**
 * @class Tile
 * @brief Representation of a tile on the map. Stores ownership and characters
 */
class PathFinder {
  public:
    PathFinder(Map const &map, Tile const &current, Tile const &target);
    std::vector<Tile> getResult();

  protected:
    static const Map* map;
    static const Tile* current;
    static const Tile* target;
    std::vector<Tile> path = vector();

    std::vector<Tile> explored = vector();
    std::vector<Tile> notExplored = vector();

  private:
    std::vector<Tile> aStarGenerator(std::vector<Tile> &path=std::vector());
    double distanceToCurrent(Tile &other);
    std::vector<Tile> unlooper(std::vector<Tile> &refPath, std::vector<Tile> &path=std::vector(), int pos=1);
    std::vector<Tile> straightener(std::vector<Tile> &refPath, std::vector<Tile> &path=std::vector(), int pos=0);
};

#endif // ILLUVATAR_PathFinder_H
