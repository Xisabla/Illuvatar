/*=========================================================================

  Project:   Illuvatar
  File:      Tile.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Tile.h"


//  --------------------------------------------------------------------------------------
//  Tile
//  --------------------------------------------------------------------------------------

Tile::Tile(int x, int y, Faction faction): Point(x, y), owner(faction) { }

Tile::Tile(Point p, Faction faction): Point(p), owner(faction) { }

//  --------------------------------------------------------------------------------------
//  Tile > GETTERS
//  --------------------------------------------------------------------------------------

Faction Tile::getOwner() { return this->owner; }

Character& Tile::getCharacter() {
    if (this->character == nullptr) {
        std::cout << "error at TileSet::getCharacter()" << std::endl;
        exit(1);
    }
    return *(this->character);
}

void Tile::setCharacter(Character* character) { this->character = character; }

bool Tile::safeFor(Faction f) { return this->owner == f; }

bool Tile::isObstacle() const { return this->obstacle; }

bool Tile::isOccupied() { return this->character != nullptr; }

//  --------------------------------------------------------------------------------------
//  Tile > SETTERS
//  --------------------------------------------------------------------------------------

void Tile::setOwner(Faction f) { this->owner = f; }

void Tile::removeOwnership() { this->owner = Faction::NoFaction; }
    
void Tile::setObstacle() { this->obstacle = true; }

void Tile::unsetObstacle() { this->obstacle = false; }
