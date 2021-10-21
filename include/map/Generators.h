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

#include <cmath>
#include <iostream>

namespace generators {

// TODO: Take predicate as argument to define the Faction

// TODO: Use a "TileSet" object instead of std::vector<Tile>
//  - Deny multiple tiles with the same position (overwrite or keep old): tiles.push(Tile,
//  [overwrite: TRUE, false])
//  - Only accept positive coordinates tiles.push(-1, -2) --> does nothing / throw error (set a
//  policy ?)
//  - Check if a tile exists: tiles.exists(x, y) / tiles.exists(p)
//  - Retrieve a tile from position: tiles.get(x, y) / tiles.get(p) (Should throw error if doesn't
//  exists)
//  - Allow creation of TileSet from Rectangle: auto tiles = TileSet(Rectangle(10, 15), Werewolves
//  (or predicate ?))
//  - Allow creation of Rectangle from set (with facultative padding): auto surface =
//  tiles.getRect(5, 2, 2, 3)
//  - Allow TileSet merging: TileSet::merge({ set1, set2, ... }, [overwrite: TRUE, false]) and
//  tiles.merge({set2, set3, ... }, [overwrite: TRUE, false])

/**
 * Generates a set of Tiles shaping a filled Disk
 * @param radius Radius of the disk
 * @param center Center of the disk
 * @param faction Faction that owns the Tiles
 * @return A set of tiles
 */
std::vector<Tile> disk(double radius, Point center, Faction faction = NoFaction);

} // namespace generators

#endif // ILLUVATAR_GENERATORS_H
