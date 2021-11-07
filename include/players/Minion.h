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

    unsigned int lifeMax = 100;
    unsigned int life = this->lifeMax;

    unsigned int energyMax = 100;
    unsigned int energyCost = 5;
    unsigned int energyEnnemyCost = 2 * this->energyCost;
    unsigned int energyLow = 20;
    unsigned int energy = this->energyMax;

    const int rangeMax = 10;
    const int rangeMin = 6;
    Direction currentDirection;

    /**
     * @brief Message exchange between two allied Minions
     * @param other The passive Minion met
     */
    void exchange(Minion& other);
    
    /**
     * @brief Fight between two ennemy Minions
     * @param other The passive Minion met
     * @return True if alive at the end of the fight
     */
    bool fightAndWin(Minion& other);

    /**
     * @brief Inflict life or energy damages to other Minion - specific to each race
     */
    virtual void attack(Minion& other) { std::cout << "error at Minion::attack(...) - forbidden usage of base definition" << std::endl; exit(1); };

  private:
    /**
     * @brief Transform the faction into ally faction
     */
    std::map<Faction, Faction> alliance = {
        { Faction::Eldars, Faction::Valars },
        { Faction::Valars, Faction::Eldars },
        { Faction::Dragons, Faction::Werewolves },
        { Faction::Werewolves, Faction::Dragons },
    };

    Result rollDice();

    /**
     * @brief Generate a path into a free direction without change of direction, until meeting obstacle or void (ignore characters)
     * @param range Limit size of the path
     * @return A mono directional path of existing Points
     */
    superTypes::DirectionalPath explorate(int range);

    /**
     * @brief List surroundings Minions and interact with them if there are any
     * @return True if interacted with someone(s)
     */
    bool interactsWithSurroundings();

    /**
     * @brief Generate the shortest path to the master, with change of direction
     * @param range Limit size of the path
     * @return A multi directional path of existing Points
     */
    superTypes::DirectionalPath findMaster(int range);

    /**
     * @brief Returns what can be found at the given position and specify into ally of ennemy if Character
     * @param point The position to verify
     */
    ThingAtPoint checkPosition(const Point& point);

    /**
     * @brief Returns what can be found at the vector arrival position and specify into ally of ennemy if Character
     * @param point Origin of vector
     * @param direction Orientation of vector
     * @return Couple of thing and vector arrival position
     */
    std::pair<ThingAtPoint, Point> checkDirection(const Point& point, Direction& direction);

    /**
     * @brief Check all positions around current minion and list allies and ennemies with their position
     * @return List of allies and ennemies with their position in check order (N to NW)
     */
    std::vector<std::pair<ThingAtPoint, Point>> checkAround();

    /**
     * @brief Setter for lifepoint
     */
    void reduceLife(unsigned int damages);

    /**
     * @brief Setter for lifepoint
     */
    void restoreLife(unsigned int heal);

    /**
     * @brief Setter for energy
     */
    void reduceEnergy(unsigned int damages);

    /**
     * @brief Setter for energy
     */
    void restoreEnergy(unsigned int heal);

    /**
     * @brief Message search onto dead ennemy minions
     * @param other The passive dead Minion
     */
    void searchCorpse(Minion& other);
};

#endif // ILLUVATAR_MINION_H
