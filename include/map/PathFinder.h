/*=========================================================================

  Project:   Illuvatar
  File:      PathFinder.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_PathFinder_H
#define ILLUVATAR_PathFinder_H

#include "map/DirectionUtils.h"
#include "map/Map.h"
#include "map/Tile.h" // remove
#include "geometry/Point.h"
#include "wip.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

namespace pathfinder {
  typedef std::vector<Point> Path;
  typedef std::vector<std::pair<Point, directionutils::Direction>> DirectionalPath;

  DirectionalPath computeShortestPath(Map& map, Point current, Point& target, directionutils::Direction initialD, unsigned int nbTile);

  Path aStarGenerator(Map& map, Path& path, Point& current, Point& target, Path& explored, Path& notExplored);

  Path unlooper(Map& map, Path& refPath, Path& path, unsigned int pos = 1);

  DirectionalPath straightenerAndCutter(Map& map, Path& refPath, DirectionalPath& path, directionutils::Direction initialD, unsigned int nbTile, unsigned int pos = 0);

  bool checkBothBridges(Map &map, DirectionalPath& path, bool alignTest, Point current, Point next, bool first, int deltaBridge);

  bool checkBridge(Map &map, DirectionalPath& path, Point bridge, bool alignTest, Point current, Point next);
};

#endif // ILLUVATAR_PathFinder_H
