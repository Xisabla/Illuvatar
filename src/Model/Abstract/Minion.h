#ifndef ILLUVATAR_MINION_H
#define ILLUVATAR_MINION_H

#include <map>
#include <set>
#include <vector>
#include "Master.h"
#include "geometry/Point.h"
#include "map/Tile.h"
#include "map/Map.h"
#include "wip.h"

class Minion
{
  public:
    void Move();

  protected:
    Map* map;
    Tile* tile;
    int energy = 100;
    const int lowEnergy = 20;
    const int rangeMax = 8;
    const int rangeMin = 2;
    Direction currentDirection;

    void Fight(Minion minion);

  private:
    static const map<ThingOnMap, Point> nextDirection = {
      { ThingOnMap::N  : Point( 0, -1) },
      { ThingOnMap::NE : Point( 1, -1) },
      { ThingOnMap::E  : Point( 1,  0) },
      { ThingOnMap::SE : Point( 1,  1) },
      { ThingOnMap::S  : Point( 0,  1) },
      { ThingOnMap::SW : Point(-1,  1) },
      { ThingOnMap::W  : Point(-1,  0) },
      { ThingOnMap::NW : Point(-1, -1) }
    }
    static const map<Faction, set<Faction>> alliances = {
      { Faction::Eldars, { Faction::Eldars, Faction::Valars } },
      { Faction::Valars, { Faction::Eldars, Faction::Valars } },
      { Faction::Dragons, { Faction::Dragons, Faction::Werewolves } },
      { Faction::Werewolves, { Faction::Dragons, Faction::Werewolves } },
    };

    void RollTheDice();
    ThingOnMap CheckDirection();
    vector<ThingOnMap> CheckAround();
    Direction Explorate(Direction mainDirection);
    Direction FindMaster(Master master);
};


#endif // ILLUVATAR_MINION_H
