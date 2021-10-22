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

    void Fight(Minion &minion);

  private:
    static const map<Direction, Point> nextDirection = {
      { Direction::N  : Point( 0, -1) },
      { Direction::NE : Point( 1, -1) },
      { Direction::E  : Point( 1,  0) },
      { Direction::SE : Point( 1,  1) },
      { Direction::S  : Point( 0,  1) },
      { Direction::SW : Point(-1,  1) },
      { Direction::W  : Point(-1,  0) },
      { Direction::NW : Point(-1, -1) }
    }
    static const map<Direction, vector<Direction>> fanDirections = {
      { Direction::N  : { Direction::NW, Direction::N,  Direction::NE } },
      { Direction::NE : { Direction::N,  Direction::NE, Direction::E  } },
      { Direction::E  : { Direction::NE, Direction::E,  Direction::SE } },
      { Direction::SE : { Direction::E,  Direction::SE, Direction::S  } },
      { Direction::S  : { Direction::SE, Direction::S,  Direction::SW } },
      { Direction::SW : { Direction::S,  Direction::SW, Direction::W  } },
      { Direction::W  : { Direction::SW, Direction::W,  Direction::NW } },
      { Direction::NW : { Direction::W,  Direction::NW, Direction::N  } }
    }
    static const map<Faction, set<Faction>> alliances = {
      { Faction::Eldars,      { Faction::Eldars,  Faction::Valars     } },
      { Faction::Valars,      { Faction::Eldars,  Faction::Valars     } },
      { Faction::Dragons,     { Faction::Dragons, Faction::Werewolves } },
      { Faction::Werewolves,  { Faction::Dragons, Faction::Werewolves } },
    };

    void RollTheDice();
    ThingOnMap CheckDirection(Direction const &direction);
    vector<ThingOnMap> CheckAround();
    Direction Explorate();
    Direction FindMaster(Master const &master);
};


#endif // ILLUVATAR_MINION_H
