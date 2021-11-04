/*=========================================================================

  Project:   Illuvatar
  File:      PathFinder.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_PATHFINDER_H
#define ILLUVATAR_PATHFINDER_H

#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"
#include "superTypes.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>


namespace pathfinder {

/**
 * @brief Compute the shortest Path between two points
 * @param map Map on which the Path will be computed
 * @param current Origin position
 * @param target Final position
 * @param maxDistance Maximum number of Tiles to use (may stop the Path before the target)
 * @return The computed Path
 */
superTypes::DirectionalPath shortest(Map& map, Point current, Point& target, unsigned int maxDistance);

/**
 * @brief Implementation of the A* algorithm to compute the shortest path between 2 Points on the
 * map
 * @return The computed path
 */
superTypes::Path AStar(Map& map, superTypes::Path& path, Point& current, Point& target, superTypes::Path& explored, superTypes::Path& unexplored);

/**
 * @brief Remove all loops on a Path
 * @return The unlooped path
 */
superTypes::Path unlooper(Map& map, superTypes::Path& refPath, superTypes::Path& path, unsigned int pos = 1);

superTypes::DirectionalPath straightenerAndCutter(Map& map,
                                      superTypes::Path& ref,
                                      superTypes::DirectionalPath& path,
                                      Direction direction,
                                      unsigned int maxDistance,
                                      unsigned int pos = 0);

bool checkBothBridges(Map& map,
                      superTypes::DirectionalPath& path,
                      bool alignTest,
                      Point current,
                      Point next,
                      bool first,
                      int deltaBridge);

bool checkBridge(Map& map,
                 superTypes::DirectionalPath& path,
                 Point bridge,
                 bool alignTest,
                 Point current,
                 Point next);
} // namespace pathfinder

#endif // ILLUVATAR_PATHFINDER_H
