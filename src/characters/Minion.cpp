/*=========================================================================

  Project:   Illuvatar
  File:      Minion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/Minion.h"

#include "map/Map.h"
#include "map/PathFinder.h"
#include "enums/DirectionUtils.h"
#include "unirand.h"

//  --------------------------------------------------------------------------------------
//  Minion
//  --------------------------------------------------------------------------------------

Minion::Minion(unsigned int x, unsigned int y, Faction faction)
: Character(x, y, faction), _master(dynamic_cast<Master*>(Map::instance().getMaster(faction))) {
    this->direction = directionutils::randDirection();
}

Minion* Minion::virtualInits() {
    this->_life = this->getLifeMax();
    this->_energy = this->getEnergyMax();
    return this;
}

//  --------------------------------------------------------------------------------------
//  Minion > GETTERS
//  --------------------------------------------------------------------------------------

Master* Minion::master() const { return _master; }

//  --------------------------------------------------------------------------------------
//  Minion > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

bool Minion::isAlive() const { return _life > 0 && _energy > 0; }

//  --------------------------------------------------------------------------------------
//  Minion > PROTECTED METHODS
//  --------------------------------------------------------------------------------------

void Minion::exchange(Minion* minion) {
    RollResult result = rollDice();

    if (result == RollResult::CriticalSuccess && !minion->messages().empty()) {
        addMessage(minion->getRandomMessage());
        return;
    }
    if (result == RollResult::Success) {
        if (!minion->messages().empty()) addMessage(minion->dropRandomMessage());
        if (!messages().empty()) minion->addMessage(dropRandomMessage());
        return;
    }
    if (result == RollResult::Failure && !minion->messages().empty()) {
        dropRandomMessage();
        return;
    }
    if (result == RollResult::CriticalFailure) {
        if (!minion->messages().empty()) minion->dropRandomMessage();
        if (!messages().empty()) dropRandomMessage();
    }
}

bool Minion::fight(Minion* minion) {
    do {
        minion->attack(minion);

        if (!minion->isAlive()) {
            searchCorpse(minion);
            return true;
        }

        minion->attack(this);
    } while (isAlive());

    minion->searchCorpse(this);

    return false;
}

void Minion::attack(Minion* minion) {
    switch(this->rollDice()) {
        case RollResult::CriticalSuccess:
            this->specialAttack(minion);
            break;

        case RollResult::Success:
            this->normalAttack(minion);
            break;

        // case failure : "miss"

        case RollResult::CriticalFailure:
            this->hurtItself();
            break;
    }
}

//  --------------------------------------------------------------------------------------
//  Minion > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void Minion::reduceEnergy(unsigned int energy) {
    _energy = std::max(static_cast<unsigned int> (0), _energy - energy);
}

void Minion::reduceLife(unsigned int life) {
    _life = std::max(static_cast<unsigned int> (0), _life - life);
}

void Minion::restoreEnergy(unsigned int heal) {
    if (this->_energy + heal < this->getEnergyMax()) this->_energy += heal;
    else this->_energy = this->getEnergyMax();
}

void Minion::restoreLife(unsigned int heal) {
    if (this->_life + heal < this->getLifeMax()) this->_life += heal;
    else this->_life = this->getLifeMax();
}

RollResult Minion::rollDice() {
    int diceResult = unirand::getValue(1, this->getDiceMaxValue());

    if (diceResult < this->getDiceCriticFailureValue()) return RollResult::CriticalFailure;

    if (diceResult <= this->getDiceFailureValue()) return RollResult::Failure;

    if (diceResult <= this->getDiceSuccessValue()) return RollResult::Success;

    return RollResult::CriticalSuccess;
}

void Minion::searchCorpse(Minion* minion) {
    RollResult result = rollDice();

    if(result == RollResult::CriticalSuccess) addMessages(minion->messages());
    if(result == RollResult::Success && !minion->messages().empty()) addMessage(minion->dropRandomMessage());
    if(result == RollResult::Failure && !messages().empty()) dropRandomMessage();
    if(result == RollResult::CriticalFailure) dropMessages();
}

void Minion::normalAttack(Minion* minion) {
    // TODO : bool to know if life or _energy ?
    minion->reduceLife(unirand::getValueAround(this->getDamages(), 2));
}

void Minion::hurtItself() {
    // TODO : bool to know if life or energy ?
    this->reduceLife(unirand::getValueAround(this->getSelfDamages()));
}

std::string Minion::getAssetPath() {
    return Character::getAssetPath() + strDirection.at(this->direction) + ".png";
}

superTypes::DirectionalPath Minion::findMaster(unsigned int range) {
    superTypes::Point target = {this->master()->x(), this->master()->y()};
    return pathfinder::shortest({this->x(), this->y()}, target, range);
}

ThingAtPoint Minion::checkPosition(const superTypes::Point& point) {
    ThingAtPoint thing = Map::instance().getThingAtPoint(point);
    if (thing != ThingAtPoint::Character) return thing;

    Faction other = Map::instance().getCharacter(point.first, point.second)->faction();
    return (other == this->faction() || other == Character::alliance.at(this->faction())) ? ThingAtPoint::Ally : ThingAtPoint::Ennemy;
}

std::pair<ThingAtPoint, superTypes::Point> Minion::checkDirection(const superTypes::Point& point, Direction& direction) {
    superTypes::Point p = Map::instance().project(point, directionutils::nextDirection.at(direction));
    return { this->checkPosition(p), p };
}

std::vector<std::pair<ThingAtPoint, superTypes::Point>> Minion::checkAround() {
    std::vector<std::pair<ThingAtPoint, superTypes::Point>> things = {};

    superTypes::Point p = { this->x(), this->y() };
    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) { // get all enum values
        std::pair<ThingAtPoint, superTypes::Point> thing = this->checkDirection(p, d);
        if (thing.first == ThingAtPoint::Ally || thing.first == ThingAtPoint::Ennemy) things.push_back(thing);
    }

    return things;
}

superTypes::DirectionalPath Minion::explore(unsigned int range) {
    std::vector<Direction> possibleDirs = {};
    superTypes::Point p = { this->x(), this->y() };

    for (Direction dir: directionutils::fanDirections.at(this->direction)) {
        if (this->checkDirection(p, dir).first == ThingAtPoint::Nothing) {
            possibleDirs.push_back(dir);
        }
    }
    if (possibleDirs.empty()) {
        for (Direction dir: directionutils::sideDirections.at(this->direction)) {
            if (this->checkDirection(p, dir).first == ThingAtPoint::Nothing) {
                possibleDirs.push_back(dir);
            }
        }
    }

    Direction direction;
    Direction opposite = directionutils::oppositeDirection.at(this->direction);
    if (!possibleDirs.empty()) {
        direction = possibleDirs[unirand::getValue(0, possibleDirs.size() - 1)];
    } else if (this->checkDirection(p, opposite).first == ThingAtPoint::Nothing) {
        direction = opposite;
    } else {
        return {}; // aucune direction : reste sur place et interagit avec trucs autours
    }

    superTypes::DirectionalPath path = {};
    superTypes::Point jump = directionutils::nextDirection.at(direction);
    superTypes::Point futurePoint = Map::instance().project(p, jump);
    int i = 0;
    do { //on sait que la première prochaine tuile est libre
        path.push_back({ futurePoint, direction });

        futurePoint = Map::instance().project(futurePoint, jump);
    } while (++i < range && Map::instance().exists(futurePoint) && this->checkDirection(futurePoint, direction).first != ThingAtPoint::Obstacle);

    return path;
}

bool Minion::interactsWithSurroundings() {
    bool interactFlag = false;
    Character* c = nullptr;
    for (std::pair<ThingAtPoint, superTypes::Point> thing: this->checkAround()) {
        switch(thing.first) {
            case ThingAtPoint::Ally:
                c = Map::instance().getCharacter(thing.second.first, thing.second.second);
                if (!c->isMaster()) {
                    this->exchange(dynamic_cast<Minion*>(c));
                }
                else if (c->faction() == this->faction()) {
                    dynamic_cast<Master*>(c)->getMessage(this);
                    dynamic_cast<Master*>(c)->giveMessage(this);
                }
                interactFlag = true;
                break;

            case ThingAtPoint::Ennemy:
                if (!this->fight(dynamic_cast<Minion*>(Map::instance().getCharacter(thing.second.first, thing.second.second)))) return true; // dead
                interactFlag = true;
                break;
        }
    }
    return interactFlag;
}

void Minion::move() {
    int range = std::max(0, unirand::getValueAround(unirand::getValue(this->getRange().first, this->getRange().second), 2));

    bool enoughEnergy = this->_energy - range * this->getEnergyCost() > this->getEnergyLow();
    superTypes::DirectionalPath path = enoughEnergy && this->gotOneMsg() ? this->explore(range) : this->findMaster(range);

    if (path.empty()) {
        this->interactsWithSurroundings();
        return;
    }

    Faction const currentFaction = this->faction();
    Faction const allyFaction = Minion::alliance.at(currentFaction);
    for (std::pair<superTypes::Point, Direction> step: path) {
        if (this->checkPosition(step.first) != ThingAtPoint::Nothing) {
            interactsWithSurroundings();
            if (!this->isAlive()) {
                //delete this; //?
            }
            return;
        }

        //tile change
        Map::instance().jump({ this->x(), this->y() }, step.first, this);
        this->_x = step.first.first;
        this->_y = step.first.second;
        this->direction = step.second;

        //energy fluctuation
        Faction owner = Tile::get(this->x(), this->y())->getOwner();
        if (owner == Faction::NoFaction) {
            this->reduceEnergy(this->getEnergyCost()); //most common - loss a bit of energy
        }
        else if (owner == currentFaction) {
            this->_energy = this->getEnergyMax(); //recover all energy
        }
        else if (owner == allyFaction) {
            this->restoreEnergy(this->getEnergyCost()); //recover a bit of energy
        }
        else {//ennemy zone
            this->reduceEnergy(this->getEnergyEnnemyCost()); //loss more energy
        }

        if (!this->_energy) {
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
