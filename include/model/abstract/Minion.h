#ifndef ILLUVATAR_MINION_H
#define ILLUVATAR_MINION_H

#include <map>
#include <set>
#include <vector>
#include "Master.h"
#include "geometry/Point.h"
#include "map/Tile.h"
#include "map/Map.h"
#include "map/PathFinder.h"
#include "map/DirectionUtils.h"
#include "wip.h"

class Minion {
  public:
    void move();

  protected:
    Master* master;
    int energy = 100;
    const int lowEnergy = 20;
    const int rangeMax = 8;
    const int rangeMin = 2;
    Direction currentDirection;

    void fight(Minion &minion);
    void exchange(Minion &minion);

  private:
    static const std::map<Faction, std::set<Faction>> alliances = {
      { Faction::Eldars,      { Faction::Eldars,  Faction::Valars     } },
      { Faction::Valars,      { Faction::Eldars,  Faction::Valars     } },
      { Faction::Dragons,     { Faction::Dragons, Faction::Werewolves } },
      { Faction::Werewolves,  { Faction::Dragons, Faction::Werewolves } },
    };

    void rollDice();
    ThingOnMap checkDirection(Tile const &tile, Direction const &direction);
    std::vector<ThingOnMap> checkAround();
    std::vector<pair<Tile*, Direction>> explorate(int const nbTile);
    std::vector<pair<Tile*, Direction>> FindMaster(int const nbTile);
    void interactsWithSurroundings();
};


#endif // ILLUVATAR_MINION_H
