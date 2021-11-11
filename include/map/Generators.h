/*=========================================================================

  Project:   Illuvatar
  File:      Generators.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_GENERATORS_H
#define ILLUVATAR_GENERATORS_H

#include "map/Tile.h"

#include <vector>

// TODO: Move to map
//  Map::generateDisk(...)
//  as commented in main:
//  Map::setPreset(...)       Map::setDefaultPreset(...)
//  map.regenerate()    OR    Map::instance()

namespace generators {
std::vector<Tile*>
disk(double radius, unsigned int centerX, unsigned int centerY, Faction owner = NoFaction);
}

#endif // ILLUVATAR_GENERATORS_H
