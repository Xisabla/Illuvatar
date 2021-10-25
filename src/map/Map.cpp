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

Map::Map(TileSet  tiles): tiles(std::move(tiles)) {
    this->gmap = new QGameMap(this->tiles.getRectAuto());
}

Map::Map(unsigned int width, unsigned int height, TileSet tiles)
: Map(Rectangle(width, height), std::move(tiles)) { }

Map::Map(Rectangle surface, TileSet tiles): tiles(std::move(tiles)) {
    // TODO: Ensure that all tiles are in the surface (Throw err)
    // TODO: this->resize(surface);
    this->gmap = new QGameMap(surface);
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

ThingOnMap getThingOnTile(int const &x, int const &y, set<Faction> const &minionAllies=set()) {
    if (!this->exist(x, y)) return ThingOnMap::Void;//determine existence de la tuile

    Faction owner = this->getTile(x, y).getOwner());//determine contenu de la tuile

    if (owner == Faction::NoFaction) return ThingOnMap::Nothing;

    return (minionAllies.find(owner) != minionAllies.end())? ThingOnMap::Ally : ThingOnMap::Ennemy;
}
