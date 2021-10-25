/*=========================================================================

Project:   Illuvatar
File:      Minion.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_MINION_H
#define ILLUVATAR_MINION_H

#include "geometry/Point.h"
#include "map/DirectionUtils.h"
#include "map/Map.h"
#include "map/PathFinder.h"
#include "map/Tile.h"
#include "model/playable/Master.h"
#include "wip.h"

#include <map>
#include <set>
#include <vector>

class Minion {
  public:
    void move();

  protected:
    Master* master;
    int energy = 100;
    const int lowEnergy = 20;
    const int rangeMax = 8;
    const int rangeMin = 2;
    directionutils::Direction currentDirection;

    void fight(Minion& minion);
    void exchange(Minion& minion);

  private:
    static const std::map<Faction, std::set<Faction>> alliances = {
        { Faction::Eldars, { Faction::Eldars, Faction::Vala } },
        { Faction::Vala, { Faction::Eldars, Faction::Vala } },
        { Faction::Dragons, { Faction::Dragons, Faction::Werewolves } },
        { Faction::Werewolves, { Faction::Dragons, Faction::Werewolves } },
    };

    void rollDice();

    ThingOnMap checkDirection(Tile const& tile, directionutils::Direction const& direction);

    std::vector<ThingOnMap> checkAround();

    pathfinder::DirectionalPath explorate(int const nbTile);

    pathfinder::DirectionalPath FindMaster(int const nbTile);

    void interactsWithSurroundings();
};

#endif // ILLUVATAR_MINION_H
