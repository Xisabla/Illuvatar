/*=========================================================================

  Project:   Illuvatar
  File:      Minion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/Minion.h"

#include "map/Map.h"
#include "unirand.h"

//  --------------------------------------------------------------------------------------
//  Minion
//  --------------------------------------------------------------------------------------

Minion::Minion(unsigned int x, unsigned int y, Faction faction)
: Character(x, y, faction), _master(dynamic_cast<Master*>(Map::instance().getMaster(faction))) { }

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
    RollResult result = roll();

    if (result == RollResult::CriticalSuccess && !minion->messages().empty())
        addMessage(minion->getRandomMessage());
    if (result == RollResult::Success) {
        if (!minion->messages().empty()) addMessage(minion->dropRandomMessage());
        if (!messages().empty()) minion->addMessage(dropRandomMessage());
    }
    if (result == RollResult::Failure && !minion->messages().empty()) dropRandomMessage();
    if (result == RollResult::CriticalFailure) {
        if (!minion->messages().empty()) minion->dropRandomMessage();
        if (!messages().empty()) dropRandomMessage();
    }
}

bool Minion::fight(Minion* minion) {
    do {
        minion->reduceLife(attack());

        if (!minion->isAlive()) {
            searchCorpse(minion);
            return true;
        }
    } while (isAlive());

    minion->searchCorpse(this);

    return false;
}

int Minion::attack() { return 100; }

//  --------------------------------------------------------------------------------------
//  Minion > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void Minion::reduceEnergy(unsigned int _energy) {
    _energy = std::max(static_cast<unsigned int> (0), _energy - _energy);
}

void Minion::reduceLife(unsigned int life) {
    _life = std::max(static_cast<unsigned int> (0), _life - life);
}

void Minion::restoreEnergy(unsigned int heal) {
    if (this->_energy + heal < this->_energyMax) this->_energy += heal;
    else this->_energy = this->_energyMax;
}

void Minion::restoreLife(unsigned int heal) {
    if (this->_life + heal < this->_lifeMax) this->_life += heal;
    else this->_life = this->_lifeMax;
}

RollResult Minion::roll() {
    // TODO: Dice objects
    return RollResult::Success;
}

void Minion::searchCorpse(Minion* minion) {
    RollResult result = roll();

    if(result == RollResult::CriticalSuccess) addMessages(minion->messages());
    if(result == RollResult::Success && !minion->messages().empty()) addMessage(minion->dropRandomMessage());
    if(result == RollResult::Failure && !messages().empty()) dropRandomMessage();
    if(result == RollResult::CriticalFailure) dropMessages();
}

void Minion::normalAttack(Minion& other) {
    // TODO : bool to know if life or _energy ?
    other.reduceLife(unirand::getValueAround(this->getDamages(), 2));
}


std::string Minion::getAsset() {
    return Character::getAsset() + strDirection.at(this->currentDirection) + ".png";
}