/*=========================================================================

  Project:   Illuvatar
  File:      MapGenerators.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_GENERATORS_H
#define ILLUVATAR_GENERATORS_H

#include "map/TileSet.h"

#include <cmath>
#include <iostream>

namespace generators {

/**
 * Generates a set of Tiles shaping a filled Disk
 * @param radius Radius of the disk
 * @param center Center of the disk
 * @param faction Faction that owns the Tiles
 * @return A set of tiles
 */
TileSet disk(double radius, const Point& center, Faction faction = NoFaction);

/**
 * Generates a set of Tiles shaping a filled Disk
 * @param radius Radius of the disk
 * @param center Center of the disk
 * @param predicate Predicate to determine the faction that owns the Tiles
 * @return A set of tiles
 */
[[maybe_unused]] TileSet
disk(double radius, const Point& center, const std::function<Faction(Point p)>& predicate);

} // namespace generators

#endif // ILLUVATAR_GENERATORS_H
