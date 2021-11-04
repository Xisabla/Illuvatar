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

[[maybe_unused]] void Map::setTile(const Point& p, Faction faction) {
    this->tiles.push(Tile(p, faction));
}

//  --------------------------------------------------------------------------------------
//  Map > GETTERS
//  --------------------------------------------------------------------------------------

bool Map::exists(const Point& p) const { return this->tiles.exists(p); }

Tile& Map::getTile(const Point& p) { return this->tiles.get(p); }

[[maybe_unused]] TileSet Map::getNeighbours(const Point& p) {
    return this->tiles.getNeighbours(p.X(), p.Y());
}

QGameMap* Map::GMap() { return this->gmap; }

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

[[maybe_unused]] void Map::resize(Rectangle surface) {
    // TODO: Use reference while manipulate tiles, surface, ... in QGameMap (+ constructor) to avoid
    //  this:
    this->gmap->setSurface(surface);
    // this->gmap->setTiles(this->tiles);
}

[[maybe_unused]] void Map::removeTile(const Point& p) {
    this->tiles.remove(p);
    this->sync();
}

void Map::sync() {
    this->gmap->setTiles(this->tiles);
    this->gmap->repaint();
}

ThingAtPoint Map::getThingAtPoint(const Point& p) {
    if (!this->exists(p)) return ThingAtPoint::Void;

    Tile& t = this->getTile(p);

    if (t.isObstacle()) return ThingAtPoint::Obstacle;
    if (t.isOccupied()) return ThingAtPoint::Character;
    return ThingAtPoint::Nothing;
}

Point Map::project(const Point& from, const Point& jump) {
    return { from.X() + jump.X(), from.Y() + jump.Y() };
}

void Map::jump(Point& from, Point& to, Character* character) {
    // todo : verify if from & to are really neighbors ?
    this->getTile(from).unsetCharacter();
    this->getTile(to).setCharacter(character);
}

Tile& Map::computeLastPosition(const Point& point, const Direction& direction) {
    Point lastCoords = Map::project(point, directionutils::computeLastJump(direction));

    // TODO: Throw exception
    if (!this->exists(lastCoords)) {
        std::cout << "error at Map::computeLastPosition(" << point << ", ...)" << std::endl;
        exit(1);
    }

    return this->getTile(lastCoords);
}

bool Map::areNeighbours(const Point& first, const Point& second) {
    return abs(first.X() - second.X()) == 1 && abs(first.Y() - second.Y()) == 1;
}
