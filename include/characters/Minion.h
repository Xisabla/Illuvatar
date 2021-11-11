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
#include "enums/RollResult.h"
#include "enums/Direction.h"
#include "enums/Faction.h"

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
    void restoreLife(unsigned int heal);
    void restoreEnergy(unsigned int heal);
    Direction getDirection() { return this->currentDirection; }

  protected:
    // - Methods -----------------------------------------------------------------------------
    void exchange(Minion* minion);
    bool fight(Minion* minion);
    int attack();

    // - Attributes --------------------------------------------------------------------------
    Master* _master;

    unsigned int _lifeMax = 100;
    unsigned int _life = this->_lifeMax;

    unsigned int _energyMax = 100;
    unsigned int _energy = this->_energyMax;
    unsigned int energyCost = 5;
    // unsigned int energyEnnemyCost = 2 * this->energyCost;
    // unsigned int energyLow = 20;
    static const int lowEnergy = 20;

    constexpr static const std::pair<int, int> range { 6, 10 };

    virtual int getDamages() = 0;
    virtual int getSelfDamages() = 0;
    virtual void specialAttack(Minion& other) = 0;
    void normalAttack(Minion& other);

    virtual int getDiceMaxValue() = 0;

    virtual int getDiceCriticFailureValue() = 0;

    virtual int getDiceFailureValue() = 0;

    virtual int getDiceSuccessValue() = 0;

    virtual std::string getAssetPath();

  private:
    // - Methods -----------------------------------------------------------------------------

    RollResult roll();

    void searchCorpse(Minion* minion);

    // TODO: DirectionalPath explore(int range);
    // TODO: DirectionalPath findMaster(int range);
    // TODO: bool interactsWithSurroundings();
    // TODO ? ThingAtPoint checkPosition(const Point& point);
    // TODO ? std::pair<ThingAtPoint, Point> checkDirection(const Point& point, Direction&
    // direction);
    // TODO ? std::vector<std::pair<ThingAtPoint, Point>> checkAround();

    // - Attributes --------------------------------------------------------------------------
    Direction currentDirection;
};


#endif // ILLUVATAR_MINION_H
