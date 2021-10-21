/*=========================================================================

  Project:   Illuvatar
  File:      Map.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Map.h"

#include <utility>

//  --------------------------------------------------------------------------------------
//  Map
//  --------------------------------------------------------------------------------------

Map::Map(const std::vector<Tile>& tiles): tiles(tiles) {
    // TODO: tiles.getRect(...) (see Generators.h)

    int xmin = INT32_MAX;
    int xmax = INT32_MIN;
    int ymin = INT32_MAX;
    int ymax = INT32_MIN;

    for (auto& t: tiles) {
        if (t.X() > xmax) xmax = t.X();
        if (t.X() < xmin) xmin = t.X();
        if (t.Y() > ymax) ymax = t.Y();
        if (t.Y() < ymin) ymin = t.Y();
    }

    // TODO: Check for valid width/height
    unsigned int width = xmax - xmin;
    unsigned int height = ymax - ymin;

    this->gmap = new QGameMap(width, height);
}

Map::Map(unsigned int width, unsigned int height, std::vector<Tile> tiles)
: Map(Rectangle(width, height), std::move(tiles)) { }

Map::Map(Rectangle surface, std::vector<Tile> tiles): tiles(tiles) {
    // TODO: Ensure all tiles are in the surface (Throw err)
    // TODO: Move this->gmap after tiles definition and give tiles to gmap
    this->gmap = new QGameMap(surface);

    for (unsigned int x = 0; x < surface.getWidth(); x++) {
        for (unsigned int y = 0; y < surface.getHeight(); y++) {
            tiles.emplace_back(x, y);
        }
    }
}

//  --------------------------------------------------------------------------------------
//  Map > GETTERS
//  --------------------------------------------------------------------------------------

QGameMap* Map::GMap() { return this->gmap; }

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Map::sync() {
    this->gmap->setTiles(this->tiles);
    this->gmap->repaint();
}
