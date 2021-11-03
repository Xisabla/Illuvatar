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
#include "players/Master.h"
#include "players/Character.h"
#include "unirand.h"
#include "wip.h"

#include <iterator>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Master;

enum class Result { CRITIC_SUCCESS, SUCCESS, FAILURE, CRITIC_FAILURE };

class Minion : public Character {
  public:
    Minion(Map& map,
           Point point,
           directionutils::Direction direction,
           Faction faction,
           Master& master);
    void move();
    bool isAlive();

  protected:
    Master& master;

    int energy = 100;
    const int lowEnergy = 20;
    const int rangeMax = 10;
    const int rangeMin = 6;
    directionutils::Direction currentDirection;

    int life = 100;

    void exchange(Minion& other);
    bool fightAndWin(Minion& other);
    virtual int attack() = 0;

  private:
    std::map<Faction, std::set<Faction>> alliances = {
        { Faction::Eldars, { Faction::Eldars, Faction::Valars } },
        { Faction::Valars, { Faction::Eldars, Faction::Valars } },
        { Faction::Dragons, { Faction::Dragons, Faction::Werewolves } },
        { Faction::Werewolves, { Faction::Dragons, Faction::Werewolves } },
    };

    Result rollDice();

    pathfinder::DirectionalPath explorate(int range);

    bool interactsWithSurroundings();

    pathfinder::DirectionalPath findMaster(int range);

    std::pair<ThingAtPoint, Point> checkDirection(const Point& point,
                                                  directionutils::Direction& direction);

    std::vector<std::pair<ThingAtPoint, Point>> checkAround();
    
    void reduceLife(int damages);

    void searchCorpse(Minion& other);
};

#endif // ILLUVATAR_MINION_H
