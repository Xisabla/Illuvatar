/*=========================================================================

  Project:   Illuvatar
  File:      Map.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Map.h"

#include "characters/Dragon.h"
#include "characters/Eldar.h"
#include "characters/Master.h"
#include "characters/Vala.h"
#include "characters/Werewolf.h"

//  --------------------------------------------------------------------------------------
//  Map
//  --------------------------------------------------------------------------------------

Preset Map::defaultPreset = Default;

Map::Map(_token t)
: Singleton(t), _domain(1, 1), _qgmap(new QGameMap), _preset(Map::defaultPreset) { }

//  --------------------------------------------------------------------------------------
//  Map > GETTERS
//  --------------------------------------------------------------------------------------

unsigned int Map::width() const { return _domain.width(); }

unsigned int Map::height() const { return _domain.height(); }

QGameMap* Map::qgmap() const { return _qgmap; }

Character* Map::getCharacter(unsigned int x, unsigned int y) {
    if (!containsCharacter(x, y))
        throw std::runtime_error("No character at position (" + std::to_string(x) + ", " +
                                 std::to_string(y) + ")");

    return _characters[{ x, y }];
}

Character* Map::getMaster(Faction faction) {
    auto found =
    std::find_if(_characters.begin(),
                 _characters.end(),
                 [faction](std::pair<std::pair<unsigned int, unsigned int>, Character*> e) {
                     return e.second->isMaster() && e.second->faction() == faction;
                 });

    if (found == std::end(_characters))
        throw std::runtime_error("No master found for faction " + strFaction.at(faction));

    return found->second;
}

//  --------------------------------------------------------------------------------------
//  Map > SETTERS
//  --------------------------------------------------------------------------------------

void Map::setPreset(Preset preset) { _preset = preset; }

void Map::setDefaultPreset(Preset preset) { Map::defaultPreset = preset; }

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Map::generate() {
    if (_preset == Turtle) {
        _domain = Domain(21, 21);

        generateDisk(7.5, 10, 10);

        generateDisk(2.8, 16, 16, Faction::Dragons);
        generateDisk(2.8, 16, 4, Faction::Eldars);
        generateDisk(2.8, 4, 16, Faction::Valars);
        generateDisk(2.8, 4, 4, Faction::Werewolves);

        new Master(16, 16, Faction::Dragons);
        new Dragon(15, 14);
        new Dragon(16, 14);
        new Dragon(17, 14);
        new Dragon(14, 15);
        new Dragon(14, 16);
        new Dragon(14, 17);

        new Master(16, 4, Faction::Eldars);
        new Eldar(15, 6);
        new Eldar(16, 6);
        new Eldar(17, 6);
        new Eldar(14, 3);
        new Eldar(14, 4);
        new Eldar(14, 5);


        new Master(4, 16, Faction::Valars);
        new Vala(3, 14);
        new Vala(4, 14);
        new Vala(5, 14);
        new Vala(6, 15);
        new Vala(6, 16);
        new Vala(6, 17);


        new Master(4, 4, Faction::Werewolves);
        new Werewolf(6, 3);
        new Werewolf(6, 4);
        new Werewolf(6, 5);
        new Werewolf(3, 6);
        new Werewolf(4, 6);
        new Werewolf(5, 6);
    }

    if (_preset == Square) {
        _domain = Domain(21, 21);

        generateSquare(0, 0, 21, 21);

        generateSquare(0, 0, 5, 5, Faction::Dragons);
        generateSquare(0, 15, 5, 20, Faction::Eldars);
        generateSquare(15, 0, 20, 5, Faction::Valars);
        generateSquare(15, 15, 20, 20, Faction::Werewolves);

        new Master(3, 3, Faction::Dragons);
        new Master(3, 18, Faction::Eldars);
        new Master(18, 3, Faction::Valars);
        new Master(18, 18, Faction::Werewolves);
        // TODO: Generate minions
    }

    sync();
}

void Map::sync() { _qgmap->repaint(); }

void Map::linkCharacter(unsigned int x, unsigned int y, Character* character) {
    _characters.insert_or_assign({ x, y }, character);
}

void Map::unlinkCharacter(Character* character) {
    auto found =
    std::find_if(_characters.begin(),
                 _characters.end(),
                 [character](std::pair<std::pair<unsigned int, unsigned int>, Character*> e) {
                     return e.second == character;
                 });

    if (found != std::end(_characters)) {
        _characters.erase(found->first);
    }
}

bool Map::containsCharacter(unsigned int x, unsigned int y) {
    return _characters.contains({ x, y });
}

bool Map::exists(const superTypes::Point& p) const {
    return Tile::exists(p.first, p.second);
}

ThingAtPoint Map::getThingAtPoint(const superTypes::Point& p) {
    if (!this->exists(p)) return ThingAtPoint::Void;

    Tile* t = Tile::get(p.first, p.second);

    // if (t->isObstacle()) return ThingAtPoint::Obstacle; //todo
    if (this->getCharacter(p.first, p.second) != nullptr) return ThingAtPoint::Character;
    return ThingAtPoint::Nothing;
}

superTypes::Point Map::computeLastPosition(const superTypes::Point& point, const Direction& direction) {
    superTypes::Point lastCoords = Map::project(point, directionutils::computeLastJump(direction));

    // TODO: Throw exception
    if (!this->exists(lastCoords)) {
        std::cout << "error at Map::computeLastPosition(" << point.first << " " << point.second << ", ...)" << std::endl;
        exit(1);
    }
    Tile* t = Tile::get(lastCoords.first, lastCoords.second);
    return { t->x(), t->y() };
}

superTypes::Point Map::project(const superTypes::Point& from, const superTypes::Point& jump) {
    return { from.first + jump.first, from.second + jump.second };
}

bool Map::areNeighbours(const superTypes::Point& first, const superTypes::Point& second) {
    return abs((int) first.first - (int) second.first) == 1 && abs((int) first.second - (int) second.second) == 1;
}

//  --------------------------------------------------------------------------------------
//  Map > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void Map::generateDisk(const double radius,
                       const unsigned int centerX,
                       const unsigned int centerY,
                       const Faction owner) {
    for (int x = static_cast<int>(-radius); x <= radius; x++) {
        for (int y = static_cast<int>(-radius); y <= radius; y++) {
            if (x * x + y * y <= static_cast<double>(radius * radius)) {
                Tile::safeCreate(x + centerX, y + centerY, owner);
            }
        }
    }
}

void Map::generateSquare(const unsigned int topX,
                         const unsigned int topY,
                         const unsigned int bottomX,
                         const unsigned int bottomY,
                         const Faction owner) {
    for (unsigned x = topX; x <= bottomX; x++) {
        for (unsigned y = topY; y <= bottomY; y++) {
            Tile::safeCreate(x, y, owner);
        }
    }
}
