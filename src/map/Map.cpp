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

bool Map::exists(const Point& p) const { return this->tiles.exists(p); }

Tile& Map::getTile(const Point& p) { return this->tiles.get(p); }

TileSet Map::getNeighbours(const Point& p) { return this->tiles.getNeighbours(p.X(), p.Y()); }

QGameMap* Map::GMap() { return this->gmap; }

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Map::resize(Rectangle surface) {
    // TODO: Use reference while manipulate tiles, surface, ... in QGameMap (+ constructor) to avoid
    // this:
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

ThingOnMap Map::getThingOnTile(const Point& p, const std::set<Faction> minionAllies) {
    if (!this->exists(p)) return ThingOnMap::Void;

    Tile t = this->getTile(p);

    if (t.isObstacle()) return ThingOnMap::Obstacle;

    if (t.belongsTo(NoFaction)) return ThingOnMap::Nothing;

    return minionAllies.find(t.getOwner()) == minionAllies.end() ? ThingOnMap::Ennemy :
                                                                   ThingOnMap::Ally;
}

Tile& Map::project(const Point& from, const Point& jump) {
    return this->getTile(Point(from.X() + jump.X(), from.Y() + jump.Y()));
}

void Map::jump(const Faction faction, Tile& from, Tile& to) {
    from.removeOwnership();
    to.setOwner(faction);
}
