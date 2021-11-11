/*=========================================================================

  Project:   Illuvatar
  File:      Generators.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Generators.h"

std::vector<Tile*> generators::disk(const double radius,
                                    const unsigned int centerX,
                                    const unsigned int centerY,
                                    const Faction owner) {
    std::vector<Tile*> tiles;

    for (int x = static_cast<int>(-radius); x <= radius; x++) {
        for (int y = static_cast<int>(-radius); y <= radius; y++) {
            if (x * x + y * y <= static_cast<double>(radius * radius)) {
                tiles.push_back(Tile::safeCreate(x + centerX, y + centerY, owner));
            }
        }
    }

    return tiles;
}
