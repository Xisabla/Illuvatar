/*=========================================================================

Project:   Illuvatar
File:      Minion.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#pragma once
#ifndef ILLUVATAR_MINION_H
#define ILLUVATAR_MINION_H

#include "geometry/Point.h"
#include "map/DirectionUtils.h"
#include "map/Map.h"
#include "map/PathFinder.h"
#include "map/Tile.h" // remove
#include "players/Master.h"
#include "wip.h"

#include <map>
#include <set>
#include <vector>
#include <iostream>

class Master;

class Minion : public Character {
  public:
    Minion(Map &map, Point point, directionutils::Direction direction, Faction faction, Master &master);
    void move();

  //protected:
    Master& master;

    int energy = 100;
    const int lowEnergy = 20;
    const int rangeMax = 10;
    const int rangeMin = 6;
    directionutils::Direction currentDirection;

    void fight(Minion& minion);
    void exchange(Minion& minion);

  //private:
    std::map<Faction, std::set<Faction>> alliances = {
        { Faction::Eldars, { Faction::Eldars, Faction::Valars } },
        { Faction::Valars, { Faction::Eldars, Faction::Valars } },
        { Faction::Dragons, { Faction::Dragons, Faction::Werewolves } },
        { Faction::Werewolves, { Faction::Dragons, Faction::Werewolves } },
    };
    
    void rollDice();

    pathfinder::DirectionalPath explorate(int const range);

    bool interactsWithSurroundings();

    pathfinder::DirectionalPath findMaster(int const range);

    ThingAtPoint checkPosition(const Point &point);

    std::pair<ThingAtPoint, Point> checkDirection(const Point &point, directionutils::Direction &direction);

    std::vector<std::pair<ThingAtPoint, Point>> checkAround();
};

#endif // ILLUVATAR_MINION_H
