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

#include "enums/Faction.h"
#include "enums/Direction.h"
#include "enums/ThingAtPoint.h"
#include "enums/Result.h"
#include "geometry/Point.h"
#include "map/Map.h"
#include "map/PathFinder.h"
#include "players/Master.h"
#include "players/Character.h"
#include "unirand.h"
#include "superTypes.h"

#include <iterator>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Master;

class Minion : public Character {
  public:
    Minion(Map& map,
           Point point,
           Direction direction,
           Faction faction,
           Master& master);

    /**
     * @brief Perform Minion turn : move on map and interact with his meetings
     */
    void move();

    /**
     * @brief Return true if Minion have lifepoints and energy
     */
    bool isAlive();

  protected:
    Master& master;

    int energy = 100;
    const int lowEnergy = 20;
    const int rangeMax = 10;
    const int rangeMin = 6;
    Direction currentDirection;

    int life = 100;

    /**
     * @brief Message exchange between two allied Minions
     * @param other The passive Minion met
     */
    void exchange(Minion& other);
    
    /**
     * @brief Message fight between two ennemy Minions
     * @param other The passive Minion met
     * @return True if alive at the end of the fight
     */
    bool fightAndWin(Minion& other);

    /**
     * @brief The computation of the damages : specific to each race
     */
    virtual int attack() { return 0; };

  private:
    std::map<Faction, std::set<Faction>> alliances = {
        { Faction::Eldars, { Faction::Eldars, Faction::Valars } },
        { Faction::Valars, { Faction::Eldars, Faction::Valars } },
        { Faction::Dragons, { Faction::Dragons, Faction::Werewolves } },
        { Faction::Werewolves, { Faction::Dragons, Faction::Werewolves } },
    };

    Result rollDice();

    superTypes::DirectionalPath explorate(int range);

    bool interactsWithSurroundings();

    superTypes::DirectionalPath findMaster(int range);

    ThingAtPoint checkPosition(const Point& point);

    std::pair<ThingAtPoint, Point> checkDirection(const Point& point, Direction& direction);

    std::vector<std::pair<ThingAtPoint, Point>> checkAround();
    
    void reduceLife(int damages);

    void searchCorpse(Minion& other);
};

#endif // ILLUVATAR_MINION_H
