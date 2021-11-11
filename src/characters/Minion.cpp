/*=========================================================================

  Project:   Illuvatar
  File:      Minion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/Minion.h"

#include "map/Map.h"

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

    if (result == CriticalSuccess && !minion->messages().empty())
        addMessage(minion->getRandomMessage());
    if (result == Success) {
        if (!minion->messages().empty()) addMessage(minion->dropRandomMessage());
        if (!messages().empty()) minion->addMessage(dropRandomMessage());
    }
    if (result == Failure && !minion->messages().empty()) dropRandomMessage();
    if (result == CriticalFailure) {
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

void Minion::reduceEnergy(unsigned int energy) {
    _energy = std::max(static_cast<unsigned int> (0), _energy - energy);
}

void Minion::reduceLife(unsigned int life) {
    _life = std::max(static_cast<unsigned int> (0), _life - life);
}

RollResult Minion::roll() {
    // TODO: Dice objects
    return Success;
}

void Minion::searchCorpse(Minion* minion) {
    RollResult result = roll();

    if(result == CriticalSuccess) addMessages(minion->messages());
    if(result == Success && !minion->messages().empty()) addMessage(minion->dropRandomMessage());
    if(result == Failure && !messages().empty()) dropRandomMessage();
    if(result == CriticalFailure) dropMessages();
}
