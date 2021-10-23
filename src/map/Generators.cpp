/*=========================================================================

  Project:   Illuvatar
  File:      MapGenerators.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Generators.h"

TileSet generators::disk(double radius, const Point& center, Faction faction) {
    TileSet set;

    int cx = center.X();
    int cy = center.Y();

    for (int x = static_cast<int>(-radius); x <= radius; x++) {
        for (int y = static_cast<int>(-radius); y <= radius; y++) {
            if (x * x + y * y <= (static_cast<double>(radius * radius))) {
                set.emplace(x + cx, y + cy, faction);
            }
        }
    }

    return set;
}

TileSet generators::disk(double radius, const Point& center, std::function<Faction(Point p)> predicate) {
    TileSet set;

    int cx = center.X();
    int cy = center.Y();

    for (int x = static_cast<int>(-radius); x <= radius; x++) {
        for (int y = static_cast<int>(-radius); y <= radius; y++) {
            if (x * x + y * y <= (static_cast<double>(radius * radius))) {
                set.emplace(x + cx, y + cy, predicate(Point(x, y)));
            }
        }
    }

    return set;
}
