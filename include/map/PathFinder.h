/*=========================================================================

  Project:   Illuvatar
  File:      PathFinder.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_PathFinder_H
#define ILLUVATAR_PathFinder_H

#include "geometry/Point.h"
#include "map/DirectionUtils.h"
#include "map/Map.h"
#include "wip.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

class Map;

namespace pathfinder {
typedef std::vector<Point> Path;
typedef std::vector<std::pair<Point, directionutils::Direction>> DirectionalPath;

/**
 * @brief Compute the shortest Path between two points
 * @param map Map on which the Path will be computed
 * @param current Origin position
 * @param target Final position
 * @param maxDistance Maximum number of Tiles to use (may stop the Path before the target)
 * @return The computed Path
 */
DirectionalPath shortest(Map& map, Point current, Point& target, unsigned int maxDistance);

/**
 * @brief Implementation of the A* algorithm to compute the shortest path between 2 Points on the
 * map
 * @return The computed path
 */
Path AStar(Map& map, Path& path, Point& current, Point& target, Path& explored, Path& unexplored);

/**
 * @brief Remove all loops on a Path
 * @return The unlooped path
 */
Path unlooper(Map& map, Path& refPath, Path& path, unsigned int pos = 1);

DirectionalPath straightenerAndCutter(Map& map,
                                      Path& ref,
                                      DirectionalPath& path,
                                      directionutils::Direction direction,
                                      unsigned int maxDistance,
                                      unsigned int pos = 0);

bool checkBothBridges(Map& map,
                      DirectionalPath& path,
                      bool alignTest,
                      Point current,
                      Point next,
                      bool first,
                      int deltaBridge);

bool checkBridge(Map& map,
                 DirectionalPath& path,
                 Point bridge,
                 bool alignTest,
                 Point current,
                 Point next);
} // namespace pathfinder

#endif // ILLUVATAR_PathFinder_H
