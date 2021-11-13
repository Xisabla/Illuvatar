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

using namespace std; //tmp

//  --------------------------------------------------------------------------------------
//  Minion
//  --------------------------------------------------------------------------------------

Minion::Minion(unsigned int x, unsigned int y, Faction faction)
: Character(x, y, faction), direction(directionutils::randDirection()), _master(dynamic_cast<Master*>(Map::instance().getMaster(faction))) {
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

bool Minion::isAlive() const {
    return _life > 0 && _energy > 0;
}

//  --------------------------------------------------------------------------------------
//  Minion > PROTECTED METHODS
//  --------------------------------------------------------------------------------------

void Minion::printAction(std::string str) {
    std::cout << "[Minion] " << this->faction() << this->getId() << ": " << str << std::endl;
}

void Minion::exchange(Minion* minion) {
    std::string msg;
    switch(rollDice()) {
        case RollResult::CriticalSuccess:
            printAction("Succès critique !");
            if (!minion->messages().empty()) {
                printAction("Copie un message de l'allié et pars en direction du maitre");
                msg = minion->dropRandomMessage();
                std::cout << "\t" << msg << std::endl;
                addMessage(msg);
            }
            else printAction("Aucun message à gagner...");
            break;
        case RollResult::Success:
            printAction("Succès !");
            if (!minion->messages().empty()) {
                printAction("Récupère un message de l'allié et pars en direction du maitre");
                msg = minion->dropRandomMessage();
                std::cout << "\t" << msg << std::endl;
                addMessage(msg);
            }
            else printAction("Aucun message à gagner...");
            if (!messages().empty()) {
                printAction("Donne un message de à l'allié qui part en direction de son maitre");
                msg = dropRandomMessage();
                std::cout << "\t" << msg << std::endl;
                minion->addMessage(msg);
            }
            else printAction("Aucun message à donner...");
            break;
        case RollResult::Failure:
            printAction("Echec !");
            if (!messages().empty()) {
                printAction("Perd un message aléatoire...");
                dropRandomMessage();
                if (messages().empty()) {
                    printAction("Pars en direction du maitre");
                }
            }
            else printAction("Aucun message à perdre...");
            break;
        case RollResult::CriticalFailure:
            printAction("Echec critique !");
            if (!messages().empty()) {
                printAction("Perd ses "+std::to_string(messages().size())+" message(s) et pars en direction du maitre...");
                dropMessages();
            }
            else printAction("Aucun message à perdre...");
            if (!minion->messages().empty()) {
                minion->dropRandomMessage();
                if (minion->messages().empty()) {
                    printAction("Allié part en direction de son maitre");
                }
            }
            else printAction("Allié n'a aucun message à perdre...");
            break;
    }
}

void Minion::fight(Minion* minion) {
    do {
        printAction("Attaque l'ennemi !");
        attack(minion);

        if (!minion->isAlive()) {
            printAction("Fouille le corps ennemi");
            searchCorpse(minion);
            Map::instance().unlinkCharacter(minion);
            Map::instance().sync();
            return;
        }

        printAction("L'ennemi réplique !");
        minion->attack(this);
    } while (isAlive());

    printAction("Se fait fouiller par l'ennemi");
    minion->searchCorpse(this);
}

void Minion::attack(Minion* minion) {
    switch(this->rollDice()) {
        case RollResult::CriticalSuccess:
            printAction("Succès critique ! Attaque spéciale !");
            this->specialAttack(minion);
            break;

        case RollResult::Success:
            printAction("Succès ! Attaque normale !");
            this->normalAttack(minion);
            break;

        case RollResult::Failure:
            printAction("Echec, rate l'ennemi...");
            break;

        case RollResult::CriticalFailure:
            printAction("Echec critique, se blesse lui même...");
            this->hurtItself();
            break;
    }
}

//  --------------------------------------------------------------------------------------
//  Minion > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void Minion::reduceEnergy(int energy) {
    _energy = std::max(0, _energy - energy);
}

void Minion::reduceLife(int life) {
    _life = std::max(0, _life - life);
}

void Minion::restoreEnergy(int heal) {
    if (this->_energy + heal < this->getEnergyMax()) this->_energy += heal;
    else this->_energy = this->getEnergyMax();
}

void Minion::restoreLife(int heal) {
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
    std::string msg;
    switch(rollDice()) {
        case RollResult::CriticalSuccess:
            printAction("Succès critique !");
            if (!minion->messages().empty()) {
                printAction("Récupère les "+std::to_string(minion->messages().size())+" message(s) de l'ennemi et pars en direction du maitre");
                for (std::string message : minion->messages()) std::cout << "\t" << message << std::endl;
                addMessages(minion->messages());
            }
            else printAction("Aucun message à gagner...");
            break;
        case RollResult::Success:
            printAction("Succès !");
            if (!minion->messages().empty()) {
                printAction("Récupère un message de l'ennemi et pars en direction du maitre");
                msg = minion->dropRandomMessage();
                std::cout << "\t" << msg << std::endl;
                addMessage(msg);
            }
            else printAction("Aucun message à gagner...");
            break;
        case RollResult::Failure:
            printAction("Echec !");
            if (!messages().empty()) {
                printAction("Perd un message aléatoire...");
                dropRandomMessage();
                if (messages().empty()) {
                    printAction("Pars en direction du maitre");
                }
            }
            else printAction("Aucun message à perdre...");
            break;
        case RollResult::CriticalFailure:
            printAction("Echec critique !");
            if (!messages().empty()) {
                printAction("Perd ses "+std::to_string(messages().size())+" message(s) et pars en direction du maitre...");
                dropMessages();
            }
            else printAction("Aucun message à perdre...");
            break;
    }
}

void Minion::normalAttack(Minion* minion) {
    int damages = std::max(1, unirand::getValueAround(this->getDamages(), 2));
    std::string nature = this->getAttackNature() == AttackNature::Physical ? "physique(s)" : "énergétique(s)";
    printAction("Inflige "+std::to_string(damages)+" points de dégâts "+nature+" à l'ennemi "+strFromFaction.at(minion->faction())+std::to_string(minion->getId()));
    switch(this->getAttackNature()) {
        case AttackNature::Physical:
            minion->reduceLife(damages);
            break;
        case AttackNature::Energetic:
            minion->reduceEnergy(damages);
            break;
    }
}

void Minion::hurtItself() {
    int damages = std::max(1, unirand::getValueAround(this->getSelfDamages(), 2));
    std::string nature = this->getAttackNature() == AttackNature::Physical ? "physique(s)" : "énergétique(s)";
    printAction("S'inflige "+std::to_string(damages)+" points de dégâts "+nature+" à lui même");
    switch(this->getAttackNature()) {
        case AttackNature::Physical:
            this->reduceLife(damages);
            break;
        case AttackNature::Energetic:
            this->reduceEnergy(damages);
            break;
    }
}

std::string Minion::getAssetPath() {
    return Character::getAssetPath() + strFromDirection.at(this->direction) + ".png";
}

superTypes::DirectionalPath Minion::findMaster(int range) {
    superTypes::Point target = {this->master()->x(), this->master()->y()};
    if (target.first < 0 || target.first > 30 || target.second < 0 || target.second > 30) return {};
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

superTypes::DirectionalPath Minion::explore(int range) {
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
    std::vector<std::pair<ThingAtPoint, superTypes::Point>> around = this->checkAround();
    if (!around.size()) {
        printAction("Rien autours");
        return false;
    }

    printAction(std::to_string(around.size())+" présence(s) autours");
    bool interactFlag = false;
    Character* c = nullptr;
    Minion* m = nullptr;
    for (std::pair<ThingAtPoint, superTypes::Point> thing: around) {
        std::cout << std::endl;
        c = Map::instance().getCharacter(thing.second.first, thing.second.second);
        if (c == nullptr) {
            printAction("\tUn obstacle");
            continue;
        }

        m = dynamic_cast<Minion*>(c);
        if (m == nullptr) {
            if (c->faction() == this->faction()) {
                printAction("\tLe maitre !");
                dynamic_cast<Master*>(c)->collectAndSendBack(this);
                interactFlag = true;
            }
            else printAction("\tUn maitre");
            continue;
        }

        switch(thing.first) {
            case ThingAtPoint::Ally:
                if (m->faction() != this->faction()) {
                    printAction("\tL'Allié "+strFromFaction.at(m->faction())+std::to_string(m->getId()));
                    this->exchange(m);
                    interactFlag = true;
                }
                else printAction("\tLe Frère "+strFromFaction.at(this->faction())+std::to_string(m->getId()));
                break;

            case ThingAtPoint::Ennemy:
                printAction("\tL'Ennemi "+strFromFaction.at(m->faction())+std::to_string(m->getId()));
                this->fight(m);
                if (!this->isAlive()) {
                    printAction("\tEst tombé au combat");
                    return true;
                }
                interactFlag = true;
                break;
        }
    }
    printAction("Fin des recontres");
    return interactFlag;
}

void Minion::move() {
    printAction("Prépare un déplacement");

    int range = std::max(1, unirand::getValueAround(unirand::getValue(this->getRange().first, this->getRange().second), 2));
    printAction("Portée de "+std::to_string(range));

    bool targetCondition = this->_energy > this->getEnergyLow() && this->gotOneMsg();
    printAction(targetCondition ? "Explore la map" : "Cherche son maitre");

    superTypes::DirectionalPath path = targetCondition ? this->explore(range) : this->findMaster(range);
    printAction("Visualise un chemin de "+std::to_string(path.size())+" case(s)");

    if (path.empty()) {
        printAction("Scannne les alentours...");
        this->interactsWithSurroundings();
        return;
    }
    Faction const currentFaction = this->faction();
    Faction const allyFaction = Minion::alliance.at(currentFaction);
    for (std::pair<superTypes::Point, Direction> step: path) {
        if (this->checkPosition(step.first) != ThingAtPoint::Nothing) {
            printAction("Rencontre quelque chose sur la route...");
            interactsWithSurroundings();
            return;
        }
        //tile change
        printAction("Se déplace...");
        Map::instance().jump(step.first, this);
        this->_x = step.first.first;
        this->_y = step.first.second;
        this->direction = step.second;
        //energy fluctuation
        Faction owner = Tile::get(this->x(), this->y())->getOwner();
        if (owner == Faction::NoFaction) {
            this->reduceEnergy(this->getEnergyCost()); // most common - loss a bit of energy
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
            printAction("Est mort de fatigue.");
            return;
        }

        printAction("Scannne les alentours...");
        if (interactsWithSurroundings()) return;
    }
}
