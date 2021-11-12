/*=========================================================================

  Project:   Illuvatar
  File:      Minion.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MINION_H
#define ILLUVATAR_MINION_H

#include "characters/Character.h"
#include "characters/Master.h"
#include "enums/ThingAtPoint.h"
#include "enums/RollResult.h"
#include "enums/Direction.h"
#include "enums/Faction.h"
#include "superTypes.h"

/**
 * @class Minion
 * @brief Short description of the class
 */
class Minion : public Character {
  public:
    Minion(unsigned int x, unsigned int y, Faction faction);

    // - Getters -----------------------------------------------------------------------------
    Master* master() const;

    // - Methods -----------------------------------------------------------------------------
    bool isAlive() const;
    void move();
    void reduceEnergy(unsigned int _energy);
    void reduceLife(unsigned int life);
    void restoreEnergy(unsigned int heal);
    void restoreLife(unsigned int heal);
    Direction getDirection() { return this->direction; }

  protected:
    // - Methods -----------------------------------------------------------------------------
    void exchange(Minion* minion);
    bool fight(Minion* minion);
    void normalAttack(Minion* minion);
    void attack(Minion* minion);
    void hurtItself();

    // - Attributes --------------------------------------------------------------------------
    Master* _master;

    //passer tous les trucs fixes en getters virtuels
    unsigned int _lifeMax = 100;
    unsigned int _life = this->_lifeMax;

    unsigned int _energyMax = 100;
    unsigned int _energy = this->_energyMax;
    unsigned int energyCost = 5;
    unsigned int energyEnnemyCost = 2 * this->energyCost;
    unsigned int energyLow = 20;
    static const int lowEnergy = 20;

    constexpr static const std::pair<int, int> range { 6, 10 };

    virtual int getDamages() = 0;
    virtual int getSelfDamages() = 0;
    virtual void specialAttack(Minion* minion) = 0;

    virtual int getDiceMaxValue() = 0;
    virtual int getDiceCriticFailureValue() = 0;
    virtual int getDiceFailureValue() = 0;
    virtual int getDiceSuccessValue() = 0;

    virtual std::string getAssetPath();

  private:
    // - Methods -----------------------------------------------------------------------------

    RollResult rollDice();

    void searchCorpse(Minion* minion);

    superTypes::DirectionalPath explore(int range);
    superTypes::DirectionalPath findMaster(int range);
    bool interactsWithSurroundings();
    std::pair<ThingAtPoint, superTypes::Point> checkDirection(const superTypes::Point& point, Direction& direction);
    ThingAtPoint checkPosition(const superTypes::Point& point);
    std::vector<std::pair<ThingAtPoint, superTypes::Point>> checkAround();

    // - Attributes --------------------------------------------------------------------------
    Direction direction;
};


#endif // ILLUVATAR_MINION_H
