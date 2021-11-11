#include "players/Minion.h"

using namespace std;
using namespace directionutils;
using namespace superTypes;
using namespace pathfinder;


Minion::Minion(Map &map, Point point, Faction faction, Master &master): Character(map, point, faction), master(master) {
    this->currentDirection = randDirection();
}

void Minion::move() {
    int range = unirand::getValue(this->rangeMin, this->rangeMax); //todo : modulate with dice throw ?

    bool enoughEnergy = this->energy - range * this->energyCost > this->energyLow;
    DirectionalPath path = enoughEnergy && this->gotOneMsg() ? this->explorate(range) : this->findMaster(range);

    if (path.empty()) {
        this->interactsWithSurroundings();
        return;
    }

    Faction const currentFaction = this->faction;
    Faction const allyFaction = Minion::alliance.at(currentFaction);
    for (pair<Point, Direction> step: path) {
        if (this->checkPosition(step.first) != ThingAtPoint::Nothing) {
            interactsWithSurroundings();
            if (!this->isAlive()) {
                //delete this; //?
            }
            return;
        }

        //tile change
        this->map.jump(this->point, step.first, this);
        this->point = step.first;
        this->currentDirection = step.second;

        //energy fluctuation
        Faction owner = this->map.getTile(this->point).getOwner();
        if (owner == Faction::NoFaction) {
            this->reduceEnergy(this->energyCost); //most common - loss a bit of energy
        }
        else if (owner == currentFaction) {
            this->energy = this->energyMax; //recover all energy
        }
        else if (owner == allyFaction) {
            this->restoreEnergy(this->energyCost); //recover a bit of energy
        }
        else {//ennemy zone
            this->reduceEnergy(this->energyEnnemyCost); //loss more energy
        }

        if (!this->energy) {
            //delete this; //?
            return;
        }

        if (interactsWithSurroundings()) {
            if (!this->isAlive()) {
                //delete this; //?
            }
            return;
        }
    }
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    for (pair<ThingAtPoint, Point> thing: this->checkAround()) {
        switch(thing.first) {
            case ThingAtPoint::Ally:
                this->exchange(dynamic_cast<Minion&>(this->map.getTile(this->point).getCharacter()));
                interactFlag = true;
                break;

            case ThingAtPoint::Ennemy:
                if (!this->fightAndWin(dynamic_cast<Minion&>(this->map.getTile(this->point).getCharacter()))) return true; // dead
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

    Faction other = this->map.getTile(point).getCharacter().getFaction();
    return (other == this->faction || other == Minion::alliance.at(this->faction)) ? ThingAtPoint::Ally : ThingAtPoint::Ennemy;
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
    int diceResult = unirand::getValue(1, this->getDiceMaxValue());

    if (diceResult < this->getDiceCriticFailureValue()){
        return Result::CRITIC_FAILURE;
    }

    else if (diceResult <= this->getDiceFailureValue()){
        return Result::FAILURE;
    }

    else if (diceResult <= this->getDiceSuccessValue()){
        return Result::SUCCESS;
    }

    else{
        return Result::CRITIC_SUCCESS;
    }
}

void Minion::exchange(Minion& other) {
    switch(this->rollDice()) {
        case Result::CRITIC_SUCCESS:
            if (other.gotMsg()) this->addMsg(other.getRandomMsg());
            break;

        case Result::SUCCESS:
            if (other.gotMsg()) this->addMsg(other.dropRandomMsg());
            if (this->gotMsg()) other.addMsg(this->dropRandomMsg());
            break;

        case Result::FAILURE:
            if (this->gotMsg()) this->dropRandomMsg();
            break;

        case Result::CRITIC_FAILURE:
            if (this->gotMsg()) this->dropRandomMsg();
            if (other.gotMsg()) other.dropRandomMsg();
            break;
    }
}

bool Minion::isAlive() {
    return this->life && this->energy;
}

void Minion::reduceLife(unsigned int damages) {
    if (this->life > damages) this->life -= damages;
    else this->life = 0;
}

void Minion::restoreLife(unsigned int heal) {
    if (this->life + heal < this->lifeMax) this->life += heal;
    else this->life = this->lifeMax;
}

void Minion::reduceEnergy(unsigned int damages) {
    if (this->energy > damages) this->energy -= damages;
    else this->energy = 0;
}

void Minion::restoreEnergy(unsigned int heal) {
    if (this->energy + heal < this->energyMax) this->energy += heal;
    else this->energy = this->energyMax;
}

void Minion::searchCorpse(Minion& other) {
    switch(this->rollDice()) {
        case Result::CRITIC_SUCCESS:
            this->addMsgList(other.getMsgList());
            break;

        case Result::SUCCESS:
            if (!other.getMsgList().empty()) this->addMsg(other.dropRandomMsg());
            break;

        case Result::FAILURE:
            if (!this->getMsgList().empty()) this->dropRandomMsg();
            break;

        case Result::CRITIC_FAILURE:
            this->dropMsgList();
            break;
    }
}

bool Minion::fightAndWin(Minion& other) {
    do {
        this->attack(other);
        if (!other.isAlive()) {
            this->searchCorpse(other);
            //delete other; //?
            return true;
        }
        other.attack(*this);
    } while(this->isAlive());

    other.searchCorpse(*this);
    return false;
}

void Minion::attack(Minion& other) {
    switch(this->rollDice()) {
        case Result::CRITIC_SUCCESS:
            this->specialAttack(other);
            break;

        case Result::SUCCESS:
            this->normalAttack(other);
            break;

        case Result::CRITIC_FAILURE:
            this->hurtItself();
            break;
    }
}

void Minion::normalAttack(Minion& other) {
    // TODO : bool to know if life or energy ?
    other.reduceLife(unirand::getValueAround(this->getDamages(), 2));
}

void Minion::hurtItself() {
    // TODO : bool to know if life or energy ?
    this->reduceLife(unirand::getValueAround(this->getSelfDamages()));
}