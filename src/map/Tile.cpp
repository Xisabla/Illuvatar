/*=========================================================================

  Project:   Illuvatar
  File:      Tile.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Tile.h"

std::ostream& operator<<(std::ostream& out, const Faction value) {
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(Faction::Eldars);
        PROCESS_VAL(Faction::Valars);
        PROCESS_VAL(Faction::Dragons);
        PROCESS_VAL(Faction::Werewolves);
        PROCESS_VAL(Faction::NoFaction);
    }
#undef PROCESS_VAL

    return out << s;
}

//  --------------------------------------------------------------------------------------
//  Tile
//  --------------------------------------------------------------------------------------

Tile::Tile(int x, int y, Faction faction): Point(x, y), owner(faction) { }

Tile::Tile(Point p, Faction faction): Point(p), owner(faction) { }

//  --------------------------------------------------------------------------------------
//  Tile > GETTERS
//  --------------------------------------------------------------------------------------

Faction Tile::getOwner() { return this->owner; }

bool Tile::belongsTo(Faction f) { return this->owner == f; }

bool Tile::isObstacle() { return this->obstacle; }

//  --------------------------------------------------------------------------------------
//  Tile > SETTERS
//  --------------------------------------------------------------------------------------

void Tile::setOwner(Faction f) { this->owner = f; }

void Tile::removeOwnership() { this->owner = NoFaction; }
    
void Tile::setObstacle() { this->obstacle = true; };

void Tile::unsetObstacle() { this->obstacle = false; };

//  --------------------------------------------------------------------------------------
//  Tile > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

bool Tile::isNeighbours(Tile& t) {
    return abs(this->X() - t.X()) == 1 && abs(this->Y() - t.Y()) == 1;
}

double Tile::distanceTo(Tile& t) {
    return sqrt(pow(this->X() - t.X(), 2) + pow(this->Y() - t.Y(), 2));
}
