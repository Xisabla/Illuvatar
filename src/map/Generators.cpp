/*=========================================================================

  Project:   Illuvatar
  File:      MapGenerators.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Generators.h"

std::vector<Tile> generators::disk(double radius, Point center, Faction faction) {
    std::vector<Tile> tiles;

    int cx = center.X();
    int cy = center.Y();

    for (int x = static_cast<int>(-radius); x <= radius; x++) {
        for (int y = static_cast<int>(-radius); y <= radius; y++) {
            if (x * x + y * y <= (static_cast<double>(radius * radius))) {
                tiles.emplace_back(x + cx, y + cy, faction);
            }
        }
    }

    return tiles;
}
