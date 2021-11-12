/*=========================================================================

  Project:   Illuvatar
  File:      Tile.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Tile.h"

#include <stdexcept>

//  --------------------------------------------------------------------------------------
//  Tile
//  --------------------------------------------------------------------------------------

unsigned int Tile::_i = 0;

std::vector<Tile*> Tile::_instances;

Tile::Tile(const unsigned int x, const unsigned int y, Faction owner)
: _id(_i++), _x(x), _y(y), _owner(owner) {
    if (Tile::exists(x, y))
        throw std::runtime_error("Tile (" + std::to_string(x) + ", " + std::to_string(y) +
                                 ") already exists");

    Tile::_instances.push_back(this);
}

Tile::~Tile() {
    auto it = std::find(_instances.begin(), _instances.end(), this);

    if (it != _instances.end()) _instances.erase(it);
}

//  --------------------------------------------------------------------------------------
//  Tile > GETTERS
//  --------------------------------------------------------------------------------------

unsigned int Tile::id() const { return _id; }

unsigned int Tile::x() const { return _x; }

unsigned int Tile::y() const { return _y; }

Faction Tile::getOwner() const { return _owner; }

std::vector<Tile*> Tile::getAll() { return _instances; }

unsigned int Tile::count() { return _instances.size(); }

Tile* Tile::get(const unsigned int x, const unsigned int y) {
    auto it = std::find_if(_instances.begin(), _instances.end(), [x, y](const Tile* t) {
        return t->x() == x && t->y() == y;
    });

    if (it == _instances.end())
        throw std::runtime_error("Tile (" + std::to_string(x) + ", " + std::to_string(y) +
                                 ") do not exist");

    return _instances[it - _instances.begin()];
}

std::vector<Tile*> Tile::getNeighbours(const unsigned int x, const unsigned int y) {
    std::vector<Tile*> neighbours;

    for (auto& t: _instances) {
        int dx = abs(static_cast<int>(x) - static_cast<int>(t->x()));
        int dy = abs(static_cast<int>(y) - static_cast<int>(t->y()));

        if ((dx == 1 && dy == 1) || (dx == 1 && dy == 0) || (dx == 0 && dy == 1))
            neighbours.push_back(t);
    }

    return neighbours;
}

//  --------------------------------------------------------------------------------------
//  Tile > SETTERS
//  --------------------------------------------------------------------------------------

void Tile::setOwnership(Faction owner) { _owner = owner; }

void Tile::removeOwnership() { _owner = Faction::NoFaction; }

//  --------------------------------------------------------------------------------------
//  Tile > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

bool Tile::isOwnedBy(Faction f) const { return _owner == f; }

bool Tile::exists(const unsigned int x, const unsigned int y) {
    return std::find_if(_instances.begin(), _instances.end(), [x, y](const Tile* t) {
               return t->x() == x && t->y() == y;
           }) != _instances.end();
}

void Tile::remove(unsigned int x, unsigned int y) {
    auto it = std::find_if(_instances.begin(), _instances.end(), [x, y](const Tile* t) {
        return t->x() == x && t->y() == y;
    });

    if (it != _instances.end()) delete _instances[it - _instances.begin()];
}

void Tile::removeAll() {
    // Use a temporary copy to iterate on to avoid seg fault
    std::vector<Tile*> refs(_instances);

    for (auto& ref: refs) delete ref;
}

Tile* Tile::safeCreate(unsigned int x, unsigned int y, Faction owner, bool overwrite) {
    // Overwrite if exists
    if (exists(x, y)) {
        Tile* t = Tile::get(x, y);

        if (overwrite && !t->isOwnedBy(owner)) t->setOwnership(owner);

        return t;
    }

    // Otherwise, create new
    return new Tile(x, y, owner);
}

//  --------------------------------------------------------------------------------------
//  Tile > PRIVATE METHODS
//  --------------------------------------------------------------------------------------
