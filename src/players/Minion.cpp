#include "players/Minion.h"

using namespace std;
using namespace directionutils;
using namespace superTypes;
using namespace pathfinder;


Minion::Minion(Map &map, Point point, Direction direction, Faction faction, Master &master): Character(map, point, faction), currentDirection(direction), master(master) {}

void Minion::move() {
    int range = unirand::getValue(this->rangeMin, this->rangeMax); //todo : modulate with dice throw ?

    bool kindCond = this->energy - range > this->lowEnergy; //todo : add msg conds at least
    DirectionalPath path = kindCond ? this->explorate(range) : this->findMaster(range);

    if (path.empty()) {
        this->interactsWithSurroundings();
        return;
    }

    for (pair<Point, Direction> step: path) {
        if (this->checkPosition(step.first) == ThingAtPoint::Nothing) {
            this->map.jump(this->point, step.first, this);
            this->point = step.first;
            this->currentDirection = step.second;
            this->energy--; // todo : this->energy += this->tile.safeFor() == this->faction ? 100 : - this->loss;

            if (interactsWithSurroundings()) {
                return;
            }

            if (!this->energy) {
                //cout << "exhausted";
                return;
            }
        }
        else {
            interactsWithSurroundings();
            return;
        }
    }
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    for (pair<ThingAtPoint, Point> thing: this->checkAround()) {
        switch(thing.first) {
            case ThingAtPoint::Ally:
                this->exchange(static_cast<Minion&>(this->map.getTile(this->point).getCharacter()));
                interactFlag = true;
                break;

            case ThingAtPoint::Ennemy:
                if (!this->fightAndWin(static_cast<Minion&>(this->map.getTile(this->point).getCharacter()))) return true; // dead
                interactFlag = true;
                break;

            //case ThingAtPoint::Master:
                //can interact with him - check if personnal master ?
                //break;
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
        direction = possibleDirs[unirand::getValue(0, possibleDirs.size() - 1)];
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

ThingAtPoint Minion::checkPosition(const Point& point) {
    ThingAtPoint thing = this->map.getThingAtPoint(point);
    if (thing != ThingAtPoint::Character) return thing;

    set<Faction>& allies = Minion::alliances.at(this->faction);
    return allies.find(this->map.getTile(point).getCharacter().getFaction()) == allies.end() ? ThingAtPoint::Ennemy : ThingAtPoint::Ally;
}

pair<ThingAtPoint, Point> Minion::checkDirection(const Point& point, Direction& direction) {
    Point p = this->map.project(point, nextDirection.at(direction));
    return { this->checkPosition(p), p };
}

vector<pair<ThingAtPoint, Point>> Minion::checkAround() {
    vector<pair<ThingAtPoint, Point>> things = {};

    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) { // get all enum values
        pair<ThingAtPoint, Point> thing = this->checkDirection(this->point, d);
        if (thing.first == ThingAtPoint::Ally || thing.first == ThingAtPoint::Ennemy) things.push_back(thing);
    }

    return things;
}

Result Minion::rollDice() {
    return Result::SUCCESS; //todo : voir avec charles
}

void Minion::exchange(Minion& other) {
    switch(this->rollDice()) {
        case Result::CRITIC_SUCCESS:
            this->addMsg(other.getRandomMsg());
            break;

        case Result::SUCCESS:
            this->addMsg(other.dropRandomMsg());
            other.addMsg(this->dropRandomMsg());
            break;

        case Result::FAILURE:
            this->dropRandomMsg();
            break;

        case Result::CRITIC_FAILURE:
            this->dropRandomMsg();
            other.dropRandomMsg();
            break;
    }
}

bool Minion::isAlive() {
    return this->life && this->energy;
}

void Minion::reduceLife(int damages) {
    this->life -= damages;
}

void Minion::searchCorpse(Minion& other) {
    switch(this->rollDice()) {
        case Result::CRITIC_SUCCESS:
            this->addMsgList(other.getMsgList());
            break;

        case Result::SUCCESS:
            this->addMsg(other.dropRandomMsg());
            break;

        case Result::FAILURE:
            this->dropRandomMsg();
            break;

        case Result::CRITIC_FAILURE:
            this->dropMsgList();
            break;
    }
}

bool Minion::fightAndWin(Minion& other) {
    do {
        other.reduceLife(this->attack());
        if (!other.isAlive()) {
            this->searchCorpse(other);
            //delete other; //risky
            return true;
        }
        this->reduceLife(other.attack());
    } while(this->isAlive());

    other.searchCorpse(*this);
    return false;
}
