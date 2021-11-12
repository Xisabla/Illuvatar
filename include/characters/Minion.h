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
#include "enums/AttackNature.h"
#include "enums/ThingAtPoint.h"
#include "enums/RollResult.h"
#include "enums/Direction.h"
#include "enums/Faction.h"
#include "superTypes.h"

class Master;

/**
 * @class Minion
 * @brief Short description of the class
 */
class Minion : public Character {
  public:
    Minion(unsigned int x, unsigned int y, Faction faction);
    Minion* virtualInits();

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
    unsigned int _life;
    unsigned int _energy;

    virtual int getLifeMax() = 0;

    virtual int getEnergyMax() = 0;
    virtual int getEnergyLow() = 0;
    virtual int getEnergyCost() = 0;
    virtual int getEnergyEnnemyCost() = 0;
    virtual std::pair<int, int> getRange() = 0;

    virtual AttackNature getAttackNature() = 0;
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

    superTypes::DirectionalPath explore(unsigned int range);
    superTypes::DirectionalPath findMaster(unsigned int range);
    bool interactsWithSurroundings();
    std::pair<ThingAtPoint, superTypes::Point> checkDirection(const superTypes::Point& point, Direction& direction);
    ThingAtPoint checkPosition(const superTypes::Point& point);
    std::vector<std::pair<ThingAtPoint, superTypes::Point>> checkAround();

    // - Attributes --------------------------------------------------------------------------
    Direction direction;
};


#endif // ILLUVATAR_MINION_H
