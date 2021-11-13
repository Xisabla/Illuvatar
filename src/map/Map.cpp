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
#include "core/Environment.h"
#include "libs/json.h"

//  --------------------------------------------------------------------------------------
//  Map
//  --------------------------------------------------------------------------------------

Map::Map(_token t)
: Singleton(t), _domain(1, 1), _qgmap(new QGameMap) { }

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
                     return e.second->faction() == faction && e.second->isMaster();
                 });

    if (found == std::end(_characters))
        return nullptr;
        //throw std::runtime_error("No master found for faction " + strFromFaction.at(faction));

    return found->second;
}

std::map<std::pair<unsigned int, unsigned int>, Character*>& Map::characters() {
    return _characters;
}

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Map::generate() {
    std::cout << "[map] Generate new game" << std::endl;
    _domain = Domain(21, 21);

    nlohmann::json env = Environment::instance()->env();
    for (auto mainBoard: env["map"]["mainBoard"]) {
        generateDisk(mainBoard["radius"],
                        mainBoard["center"]["x"],
                        mainBoard["center"]["y"]);
    }

    for (auto safeZone: env["map"]["safeZones"]) {
        generateDisk(safeZone["radius"],
                        safeZone["center"]["x"],
                        safeZone["center"]["y"],
                        strToFaction.at(safeZone["faction"]));
    }

    for (auto race: env["characters"]) {
        Faction faction = strToFaction.at(race["faction"]);
        (new Master(race["master"]["position"]["x"], race["master"]["position"]["y"], faction))->printAction("naissance");

        switch (faction) {
            case Faction::Dragons:
                for (auto pos: race["minion"]["positions"])
                    (new Dragon(pos["x"], pos["y"]))->virtualInits()->printAction("naissance");
                break;

            case Faction::Eldars:
                for (auto pos: race["minion"]["positions"])
                    (new Eldar(pos["x"], pos["y"]))->virtualInits()->printAction("naissance");
                break;

            case Faction::Valars:
                for (auto pos: race["minion"]["positions"])
                    (new Vala(pos["x"], pos["y"]))->virtualInits()->printAction("naissance");
                break;

            case Faction::Werewolves:
                for (auto pos: race["minion"]["positions"])
                    (new Werewolf(pos["x"], pos["y"]))->virtualInits()->printAction("naissance");
                break;
        }
        std::cout << std::endl;
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

void Map::removeAllCharacters() {
    for (auto& e: _characters) delete e.second;

    _characters = {};
}

bool Map::exists(const superTypes::Point& p) const { return Tile::exists(p.first, p.second); }

ThingAtPoint Map::getThingAtPoint(const superTypes::Point& p) {
    if (!this->exists(p)) return ThingAtPoint::Void;

    Tile* t = Tile::get(p.first, p.second);
    // if (t->isObstacle()) return ThingAtPoint::Obstacle; //todo
    if (this->containsCharacter(p.first, p.second)) return ThingAtPoint::Character;
    return ThingAtPoint::Nothing;
}

superTypes::Point Map::computeLastPosition(const superTypes::Point& point,
                                           const Direction& direction) {
    superTypes::Point lastCoords = Map::project(point, directionutils::computeLastJump(direction));

    // TODO: Throw exception
    if (!this->exists(lastCoords)) {
        std::cout << "error at Map::computeLastPosition(" << point.first << " " << point.second
                  << ", ...)" << std::endl;
        exit(1);
    }
    Tile* t = Tile::get(lastCoords.first, lastCoords.second);
    return { t->x(), t->y() };
}

superTypes::Point Map::project(const superTypes::Point& from, const superTypes::Point& jump) {
    return { from.first + jump.first, from.second + jump.second };
}

bool Map::areNeighbours(const superTypes::Point& first, const superTypes::Point& second) {
    return abs((int) first.first - (int) second.first) == 1 &&
           abs((int) first.second - (int) second.second) == 1;
}

void Map::jump(superTypes::Point newPos, Character* character) {
    // todo : verify if from & to are really neighbors ?
    Map::instance().unlinkCharacter(character);
    Map::instance().linkCharacter(newPos.first, newPos.second, character);
    Map::instance().sync();
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