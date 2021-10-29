#include "players/Minion.h"

using namespace std;
using namespace directionutils;
using namespace pathfinder;


Minion::Minion(Map &map, Tile &Tile, Faction faction, Master &master): Character(map, tile, faction), master(master) {}

void Minion::move() {
    int nbTile = rand() % (this->rangeMax - this->rangeMin + 1) + this->rangeMin;

    bool kindCond = this->energy - nbTile > this->lowEnergy;
    DirectionalPath path = kindCond ? this->explorate(nbTile) : this->findMaster(nbTile);

    if (path.empty()) {
        this->interactsWithSurroundings();
        return;
    }

    for (pair<Tile, Direction> step: path) {
        if (this->checkDirection(step.first, step.second) == ThingOnTile::Nothing) {
            this->map.jump(this->faction, this->tile, step.first);
            this->tile = step.first;
            this->currentDirection = step.second;
            this->energy--;
        }

        if (interactsWithSurroundings()) return;
    }
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    for (ThingOnTile thing: this->checkAround()) {
        switch(thing) {
            case ThingOnTile::Ally:
                //échange les infos
                interactFlag = true;
                break;

            case ThingOnTile::Ennemy:
                // fight
                interactFlag = true;
                break;
        }
    }
    return interactFlag;
}

DirectionalPath Minion::explorate(int const nbTile) {
    vector<Direction> possibleDirs = {};

    for (Direction dir: fanDirections.at(this->currentDirection)) {
        if (this->checkDirection(this->tile, dir) == ThingOnTile::Nothing)
            possibleDirs.push_back(dir);
    }

    Direction direction;
    Direction opposite = oppositeDirection.at(this->currentDirection);
    if (!possibleDirs.empty()) {
        direction = possibleDirs[rand() % possibleDirs.size()];
    } else if (this->checkDirection(this->tile, opposite) == ThingOnTile::Nothing) {
        direction = opposite;
    } else
        return {}; // aucune direction : reste sur place et interagit avec trucs autours

    DirectionalPath path = {};
    Tile& futureTile = this->map.getTile(this->map.project(this->tile.getPoint(), nextDirection.at(direction)));
    int i = 0;
    do {
        path.push_back({ futureTile, direction }); //on sait que la première prochaine tuile est libre
        futureTile = this->map.getTile(this->map.project(futureTile.getPoint(), nextDirection.at(direction)));
    } while (++i < nbTile && this->checkDirection(futureTile, direction) != ThingOnTile::Obstacle);

    return path;
}

DirectionalPath Minion::findMaster(int const nbTile) {
    return computeShortestPath(this->map, this->tile, this->master.getTile(), this->currentDirection, nbTile);
}


ThingOnTile Minion::checkDirection(Tile &tile, Direction &direction) {
    return this->map.getThingOnTile(this->map.project(tile, nextDirection.at(direction)), Minion::alliances.at(this->faction));
}

vector<ThingOnTile> Minion::checkAround() {
    vector<ThingOnTile> things = {};

    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) { // get all enum values
        ThingOnTile thing = this->checkDirection(this->tile, d);
        if (thing == ThingOnTile::Ally || thing == ThingOnTile::Ennemy) things.push_back(thing);
    }

    return things;
}

void Minion::rollDice() { }

void Minion::fight(Minion& other) { }

void Minion::exchange(Minion& other) { }
