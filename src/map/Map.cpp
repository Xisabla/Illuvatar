/*=========================================================================

  Project:   Illuvatar
  File:      Map.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Map.h"

std::ostream& operator<<(std::ostream& out, const ThingAtPoint value) {
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(ThingAtPoint::Void);
        PROCESS_VAL(ThingAtPoint::Nothing);
        PROCESS_VAL(ThingAtPoint::Obstacle);
        PROCESS_VAL(ThingAtPoint::Ennemy);
        PROCESS_VAL(ThingAtPoint::Ally);
    }
#undef PROCESS_VAL

    return out << s;
}

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

ThingAtPoint Map::getThingAtPoint(const Point& p, const std::set<Faction> minionAllies) {
    if (!this->exists(p)) return ThingAtPoint::Void;

    Tile t = this->getTile(p);

    if (t.isObstacle()) return ThingAtPoint::Obstacle;

    if (t.belongsTo(NoFaction)) return ThingAtPoint::Nothing;

    return minionAllies.find(t.getOwner()) == minionAllies.end() ? ThingAtPoint::Ennemy :
                                                                   ThingAtPoint::Ally;
}

Point Map::project(const Point& from, const Point& jump) {
    return Point(from.X() + jump.X(), from.Y() + jump.Y());
}

void Map::jump(const Minion minion, Point& from, Point& to) {
    // todo : equivalent of thoses
    this->getTile(from).removeOwnership();
    this->getTile(to).setOwner(minion.getFaction());
}

Tile& Map::computeLastPosition(const Point &point, const directionutils::Direction &direction) {
    Point lastCoords = this->project(point, directionutils::computeLastJump(direction));

    if (!this->exists(lastCoords)) {
        std::cout << "error at Map::computeLastPosition(" << point << ", ...)" << std::endl;
        exit(1);
    }

    return this->getTile(lastCoords);
}

bool Map::areNeighbours(const Point& first, const Point& second) {
    return abs(first.X() - second.X()) == 1 && abs(first.Y() - second.Y()) == 1;
}
