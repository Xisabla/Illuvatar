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
superTypes::DirectionalPath shortest(superTypes::Point current, superTypes::Point& target, unsigned int maxDistance);

/**
 * Compute the distance between the current Point and another one
 * @param p1 First point to compute the distance
 * @param p2 Second point to compute the distance
 * @return The distance computed
 */
double distanceTo(superTypes::Point& p1, superTypes::Point& p2);

/**
 * @brief Implementation of the A* algorithm to compute the shortest path between 2 Points on the
 * map
 * @return The computed path
 */
superTypes::Path AStar(superTypes::Path& path, superTypes::Point& current, superTypes::Point& target, superTypes::Path& explored, superTypes::Path& unexplored);

/**
 * @brief Remove all loops on a Path by taking the last neighbour of each point
 * @return The unlooped path
 */
superTypes::Path unlooper(superTypes::Path& refPath, superTypes::Path& path, unsigned int pos = 1);

/**
 * @brief Remove all bridges on a Path by detecting pattern and add direction at each step
 * @return The unbridged, directed path
 */
superTypes::DirectionalPath straightenerAndCutter(superTypes::Path& ref,
                                      superTypes::DirectionalPath& path,
                                      Direction direction,
                                      unsigned int maxDistance,
                                      unsigned int pos = 0);

/**
 * @brief Verify pattern on both side of both axis
 * @param current The departure of a potential bridge
 * @param next The arrival of a potential bridge
 * @return True if a bridge is detected
 */
bool checkAllBridges(superTypes::DirectionalPath& path, superTypes::Point current, superTypes::Point next);

/**
 * @brief Verify pattern on both side of a secondary axis for a given primary axis
 * @param alignTest The result of primary axis alignment logic test
 * @param current The departure of a potential bridge
 * @param next The arrival of a potential bridge
 * @param first The secondary axis selector : false for Y and true for X
 * @param deltaBridge The gap between current and next on the secondary axis
 * @return True if a bridge is detected
 */
bool checkBothBridges(superTypes::DirectionalPath& path,
                      bool alignTest,
                      superTypes::Point current,
                      superTypes::Point next,
                      bool first,
                      int deltaBridge);

/**
 * @brief Verify pattern on one direction (primary and secondary axis fixed) and add points to path if good
 * @param bridge The point that can replace the potential bridge
 * @param alignTest  The result of secondary axis alignment logic test
 * @param current The departure of a potential bridge
 * @param next The arrival of a potential bridge
 * @return True if a bridge is detected and added to the path
 */
bool checkBridge(superTypes::DirectionalPath& path,
                 superTypes::Point bridge,
                 bool alignTest,
                 superTypes::Point current,
                 superTypes::Point next);
} // namespace pathfinder

#endif // ILLUVATAR_PATHFINDER_H
