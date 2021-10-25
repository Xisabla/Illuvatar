/*=========================================================================

  Project:   Illuvatar
  File:      Map.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Map.h"

//  --------------------------------------------------------------------------------------
//  Map
//  --------------------------------------------------------------------------------------

Map::Map(TileSet tiles): tiles(std::move(tiles)) {
    this->gmap = new QGameMap(this->tiles.getRectAuto(), this->tiles);
}

[[maybe_unused]] Map::Map(unsigned int width, unsigned int height, TileSet tiles)
: Map(Rectangle(width, height), std::move(tiles)) { }

Map::Map(Rectangle surface, TileSet tiles): tiles(std::move(tiles)) {
    this->gmap = new QGameMap(surface, this->tiles);
}

//  --------------------------------------------------------------------------------------
//  Map > SETTERS
//  --------------------------------------------------------------------------------------

void Map::setTile(const Point& p, Faction faction) { this->tiles.push(Tile(p, faction)); }

//  --------------------------------------------------------------------------------------
//  Map > GETTERS
//  --------------------------------------------------------------------------------------

Tile& Map::getTile(const Point& p) { return this->tiles.get(p); }

TileSet Map::getNeighbours(const Point& p) { return this->tiles.getNeighbours(p.X(), p.Y()); }

QGameMap* Map::GMap() { return this->gmap; }

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Map::resize(Rectangle surface) {
    // TODO: Use reference while manipulate tiles, surface, ... in QGameMap (+ constructor) to avoid this:
    this->gmap->setSurface(surface);
    // this->gmap->setTiles(this->tiles);
}

void Map::removeTile(const Point& p) {
    this->tiles.remove(p);
    this->sync();
}

void Map::sync() {
    this->gmap->setTiles(this->tiles);
    this->gmap->repaint();
}
