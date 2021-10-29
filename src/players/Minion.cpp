#include "players/Minion.h"

/*


using namespace std;
using namespace directionutils;
using namespace pathfinder;

void Minion::move() {
    int nbTile = rand() % (this->rangeMax - this->rangeMin + 1) + this->rangeMin;

    DirectionalPath path =
    (this->energy - nbTile > this->lowEnergy) ? this->Explorate(nbTile) : this->FindMaster(nbTile);

    if (path.empty()) {
        interactsWithSurroundings();
        return;
    }

    for (pair<Tile*, Direction> step: path) {
        if (this->CheckDirection(step.first, step.second) == ThingOnMap::Nothing) {
            this->tile.setOwner(Faction::NoFaction);
            this->tile = step.first;
            this->tile.setOwner(this->faction);

            this->currentDirection = step.second;
            this->energy--;
        }

        if (interactsWithSurroundings()) return;
    }
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    for (ThingOnMap thing: this->CheckAround()) {
        swith(thing) {
            case ThingOnMap::Ally:
                //échange les infos
                interactFlag = true;
                break;

            case ThingOnMap::Ennemy:
                // fight
                interactFlag = true;
                break;
        }
    }
    return interactFlag;
}

DirectionalPath Minion::explorate(int const nbTile) {
    vector<Direction> possibleDirs = vector();

    for (Direction dir: fanDirections[this->currentDirection]) {
        if (this->CheckDirection(this->tile, dir) == ThingOnMap::Nothing)
            possibleDirs.push_back(dir);
    }

    Direction direction;
    if (!possibleDirs.empty()) {
        direction = possibleDirs[rand() % possibleDirs.size()];
    } else if (this->CheckDirection(this->tile, oppositeDirection[this->currentDirection]) ==
               ThingOnMap::Nothing) {
        direction = oppositeDirection[this->currentDirection];
    } else
        return vector(); // reste sur place et interagit avec trucs autours

    DirectionalPath path = vector();
    Tile* futureTile = this->tile;
    int i = 0;
    do {
        int nextX = futureTile->X() + nextDirection[direction]->X();
        int nextY = futureTile->Y() + nextDirection[direction]->Y();
        futureTile = this->map.getTile(nextX, nextY);
        path.push_back({ futureTile, direction });
    } while (++i < nbTile && this->CheckDirection(futureTile, direction) != ThingOnMap::Obstacle);

    return path;
}

DirectionalPath Minion::findMaster(int const nbTile) {
    return computeShortestPath(this->map, this->tile, this->master->tile, this->currentDirection, nbTile);
}

ThingOnMap Minion::checkDirection(Tile &tile, Direction &direction) {
    int nextX = tile.X() + nextDirection.at(direction)->X();
    int nextY = tile.Y() + nextDirection.at(direction)->Y();

    return this->map->getThingOnTile(nextX, nextY, Minion::alliances[this->faction]);
}

vector<ThingOnMap> Minion::checkAround() {
    vector<ThingOnMap> things = vector();

    for (Direction direction = Direction::Begin; direction != Direction::End;
         ++direction) { // get all enum values
        ThingOnMap thing = CheckDirection(this->tile, direction);
        if (thing == ThingOnMap::Ally || thing == ThingOnMap::Ennemy) things.push_back(thing);
    }

    return things;
}

void Minion::rollDice() { }

void Minion::fight(Minion& minion) { }

void Minion::exchange(Minion& minion) { }

*/