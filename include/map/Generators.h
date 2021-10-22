/*=========================================================================

  Project:   Illuvatar
  File:      MapGenerators.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_GENERATORS_H
#define ILLUVATAR_GENERATORS_H

#include "map/Map.h"
#include "map/Tile.h"
#include "map/TileSet.h"

#include <cmath>
#include <iostream>

namespace generators {

// TODO: Take predicate as argument to define the Faction

/**
 * Generates a set of Tiles shaping a filled Disk
 * @param radius Radius of the disk
 * @param center Center of the disk
 * @param faction Faction that owns the Tiles
 * @return A set of tiles
 */
TileSet disk(double radius, const Point& center, Faction faction = NoFaction);

} // namespace generators

#endif // ILLUVATAR_GENERATORS_H
