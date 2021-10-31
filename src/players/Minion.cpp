#include "players/Minion.h"

using namespace std;
using namespace directionutils;
using namespace pathfinder;


Minion::Minion(Map &map, Tile &tile, Faction faction, Master &master): Character(map, tile, faction), master(master), currentDirection(Direction::N) {}

void Minion::move() {
    int nbTile = rand() % (this->rangeMax - this->rangeMin + 1) + this->rangeMin; //todo : modulate with dice throw ?

    bool kindCond = this->energy - nbTile > this->lowEnergy; //todo : add msg conds at least
    DirectionalPath path = kindCond ? this->explorate(nbTile) : this->findMaster(nbTile);

    if (path.empty()) {
        this->interactsWithSurroundings();
        return;
    }

    for (pair<Tile, Direction> step: path) {
        if (this->checkDirection(step.first, step.second).first == ThingOnTile::Nothing) {
            this->map.jump(this->faction, this->tile, step.first); // todo : add this to args
            this->tile = step.first;
            this->currentDirection = step.second;
            this->energy--; // todo : this->energy += this->tile.safeFor() == this->faction ? this->recovery : - this->loss;
        }

        if (interactsWithSurroundings()) return;
    }
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    for (pair<ThingOnTile, Point> thing: this->checkAround()) {
        switch(thing.first) {
            case ThingOnTile::Ally:
                //échange les infos : todo get minion from tile
                interactFlag = true;
                break;

            case ThingOnTile::Ennemy:
                // fight : todo get minion from tile
                interactFlag = true;
                break;
        }
    }
    return interactFlag;
}

DirectionalPath Minion::explorate(int const nbTile) {
    vector<Direction> possibleDirs = {};

    for (Direction dir: fanDirections.at(this->currentDirection)) {
        if (this->checkDirection(this->tile, dir).first == ThingOnTile::Nothing) {
            possibleDirs.push_back(dir);
        }
    }

    Direction direction;
    Direction opposite = oppositeDirection.at(this->currentDirection);
    if (!possibleDirs.empty()) {
        direction = possibleDirs[rand() % possibleDirs.size()];
    } else if (this->checkDirection(this->tile, opposite).first == ThingOnTile::Nothing) {
        direction = opposite;
    } else {
        return {}; // aucune direction : reste sur place et interagit avec trucs autours
    }

    DirectionalPath path = {};
    Point jump = nextDirection.at(direction);
    Point futurePoint = this->map.project(this->tile.getPoint(), jump);
    Tile futureTile = this->tile; // can't be NULL
    int i = 0;
    do { //on sait que la première prochaine tuile est libre
        futureTile = this->map.getTile(futurePoint);
        path.push_back({ futureTile, direction });

        futurePoint = this->map.project(futurePoint, jump);
    } while (++i < nbTile && this->map.exists(futurePoint) && this->checkDirection(futureTile, direction).first != ThingOnTile::Obstacle);

    return path;
}

DirectionalPath Minion::findMaster(int const nbTile) {
    return computeShortestPath(this->map, this->tile, this->master.getTile(), this->currentDirection, nbTile);
}


pair<ThingOnTile, Point> Minion::checkDirection(Tile &tile, Direction &direction) {
    Point p = this->map.project(tile, nextDirection.at(direction));
    return { this->map.getThingOnTile(p, Minion::alliances.at(this->faction)), p };
}

vector<pair<ThingOnTile, Point>> Minion::checkAround() {
    vector<pair<ThingOnTile, Point>> things = {};

    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) { // get all enum values
        pair<ThingOnTile, Point> thing = this->checkDirection(this->tile, d);
        if (thing.first == ThingOnTile::Ally || thing.first == ThingOnTile::Ennemy) things.push_back(thing);
    }

    return things;
}

void Minion::rollDice() { }

void Minion::fight(Minion& other) { }

void Minion::exchange(Minion& other) { }
