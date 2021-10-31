#include "players/Minion.h"
#include <iterator>

using namespace std;
using namespace directionutils;
using namespace pathfinder;


Minion::Minion(Map &map, Point point, Direction direction, Faction faction, Master &master): Character(map, point, faction), currentDirection(direction), master(master) {}

void Minion::move() {
    int range = rand() % (this->rangeMax - this->rangeMin + 1) + this->rangeMin; //todo : modulate with dice throw ?
    cout << endl << "range : " << range << endl;

    bool kindCond = this->energy - range > this->lowEnergy; //todo : add msg conds at least
    cout << (kindCond ? "explo" : "master") << endl;
    DirectionalPath path = kindCond ? this->explorate(range) : this->findMaster(range);
    cout << "nb moves visualized : " << path.size() << endl;

    if (path.empty()) {
        cout << "empty path : fight" << endl;  
        this->interactsWithSurroundings();
        return;
    }

    for (pair<Point, Direction> step: path) {
        cout << step.first << " - " << step.second << endl;
        if (this->checkDirection(step.first, step.second).first == ThingAtPoint::Nothing) {
            this->map.jump(this->point, step.first, this->faction); // todo : add this to args
            this->point = step.first;
            this->currentDirection = step.second;
            this->energy--; // todo : this->energy += this->tile.safeFor() == this->faction ? 100 : - this->loss;
            cout << "new pos : " << this->point << " - " << this->currentDirection << endl;

            if (interactsWithSurroundings()) {
                cout << "interacted with neighbors" << endl;
                return;
            }

            if (!this->energy) {
                cout << "exhausted";
                return;
            }
        }
        else {
            cout << "something or nothing on the road" << endl;
            interactsWithSurroundings();
            return;
        }
    }

    cout << "no neighbors !" << endl;
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    for (pair<ThingAtPoint, Point> thing: this->checkAround()) {
        switch(thing.first) {
            case ThingAtPoint::Ally:
                //échange les infos : todo get minion from tile
                interactFlag = true;
                break;

            case ThingAtPoint::Enemy:
                // fight : todo get minion from tile
                interactFlag = true;
                break;
        }
    }
    return interactFlag;
}

DirectionalPath Minion::explorate(int const range) {
    vector<Direction> possibleDirs = {};

    for (Direction dir: fanDirections.at(this->currentDirection)) {
        if (this->checkDirection(this->point, dir).first == ThingAtPoint::Nothing) {
            possibleDirs.push_back(dir);
        }
    }
    if (possibleDirs.empty()) {
        for (Direction dir: sideDirections.at(this->currentDirection)) {
            if (this->checkDirection(this->point, dir).first == ThingAtPoint::Nothing) {
                possibleDirs.push_back(dir);
            }
        }
    }

    Direction direction;
    Direction opposite = oppositeDirection.at(this->currentDirection);
    if (!possibleDirs.empty()) {
        direction = possibleDirs[rand() % possibleDirs.size()];
    } else if (this->checkDirection(this->point, opposite).first == ThingAtPoint::Nothing) {
        direction = opposite;
    } else {
        return {}; // aucune direction : reste sur place et interagit avec trucs autours
    }

    DirectionalPath path = {};
    Point jump = nextDirection.at(direction);
    Point futurePoint = this->map.project(this->point, jump);
    int i = 0;
    do { //on sait que la première prochaine tuile est libre
        path.push_back({ futurePoint, direction });

        futurePoint = this->map.project(futurePoint, jump);
    } while (++i < range && this->map.exists(futurePoint) && this->checkDirection(futurePoint, direction).first != ThingAtPoint::Obstacle);

    return path;
}

DirectionalPath Minion::findMaster(int const range) {
    return shortest(this->map, this->point, this->master.getPoint(), range);
}

pair<ThingAtPoint, Point> Minion::checkDirection(const Point &point, Direction &direction) {
    Point p = this->map.project(point, nextDirection.at(direction));
    return { this->map.getThingAtPoint(p, Minion::alliances.at(this->faction)), p };
}

vector<pair<ThingAtPoint, Point>> Minion::checkAround() {
    vector<pair<ThingAtPoint, Point>> things = {};

    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) { // get all enum values
        pair<ThingAtPoint, Point> thing = this->checkDirection(this->point, d);
        if (thing.first == ThingAtPoint::Ally || thing.first == ThingAtPoint::Enemy) things.push_back(thing);
    }

    return things;
}

void Minion::rollDice() { }

void Minion::fight(Minion& other) { }

void Minion::exchange(Minion& other) { }
