/*=========================================================================

  Project:   Illuvatar
  File:      Tile.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_PathFinder_H
#define ILLUVATAR_PathFinder_H

#include "map/DirectionUtils.h"
#include "map/Map.h"
#include "map/Tile.h"
#include "wip.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

typedef std::vector<std::pair<Tile, DirectionUtils::Direction>> DirectionalPath;

// TODO: Make PathFinder class a set of methods (ns: pathfinder)

/**
 * @class Tile
 * @brief Representation of a tile on the map. Stores ownership and characters
 */
class PathFinder {
  public:
    PathFinder(Map const& map,
               Tile const& current,
               Tile const& target,
               DirectionUtils::Direction const& initialDirection);

    std::vector<std::pair<Tile, DirectionUtils::Direction>> getResult(unsigned int nbTile);

  protected:
    Map& map;
    const Tile current;
    const Tile target;
    const DirectionUtils::Direction initialDirection;
    std::vector<std::pair<Tile, DirectionUtils::Direction>> path = {};

    std::vector<Tile> explored = {};
    std::vector<Tile> notExplored = {};

  private:
    std::vector<Tile> aStarGenerator(std::vector<Tile>& path);

    double distanceToCurrent(Tile& other);

    std::vector<Tile> unlooper(std::vector<Tile>& refPath, std::vector<Tile>& path, int pos = 1);

    std::vector<std::pair<Tile, DirectionUtils::Direction>>
    straightener(std::vector<Tile>& refPath, DirectionalPath& path, int pos = 0);

    bool checkBothBridges(std::vector<std::pair<Tile, DirectionUtils::Direction>>& path,
                          bool alignTest,
                          Tile current,
                          Tile next,
                          bool first,
                          int deltaBridge);

    bool checkBridge(std::vector<std::pair<Tile, DirectionUtils::Direction>>& path,
                     Tile bridge,
                     bool alignTest,
                     Tile current,
                     Tile next);
};

#endif // ILLUVATAR_PathFinder_H
