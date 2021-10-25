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

// TODO: Make PathFinder class a set of methods (ns: pathfinder)

/**
 * @class Tile
 * @brief Representation of a tile on the map. Stores ownership and characters
 */
namespace pathfinder {
  typedef std::vector<Tile> Path;
  typedef std::vector<std::pair<Tile, directionutils::Direction>> DirectionalPath;

  DirectionalPath computeShortestPath(unsigned int nbTile);

  Path aStarGenerator(Map& map, Path& path, Tile current, Tile& target, Path& explored, Path& notExplored);

  Path unlooper(Map& map, Path& refPath, Path& path, int pos = 1);

  DirectionalPath straightener(Map& map, Path& refPath, DirectionalPath& path, Direction initialD, int pos = 0);

  bool checkBothBridges(Map &map, DirectionalPath& path, bool alignTest, Tile current, Tile next, bool first, int deltaBridge);

  bool checkBridge(Map &map, DirectionalPath& path, Tile bridge, bool alignTest, Tile current, Tile next);

};

#endif // ILLUVATAR_PathFinder_H
