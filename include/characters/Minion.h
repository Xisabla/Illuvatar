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
#include "core/Roll.h"

/**
 * @class Minion
 * @brief Short description of the class
 */
class Minion : public Character {
  public:
    Minion(unsigned int x, unsigned int y, Faction faction /*, Direction direction = DEFAULT */);

    // - Getters -----------------------------------------------------------------------------
    Master* master() const;

    // - Methods -----------------------------------------------------------------------------
    bool isAlive() const;
    void move();

  protected:
    // - Methods -----------------------------------------------------------------------------
    void exchange(Minion* minion);
    bool fight(Minion* minion);
    int attack();

    // - Attributes --------------------------------------------------------------------------
    Master* _master;

    unsigned int _life = 100;
    unsigned int _energy = 100;

    static const int lowEnergy = 20;
    constexpr static const std::pair<int, int> range { 6, 10 };
    // TODO: Direction direction;

  private:
    // - Methods -----------------------------------------------------------------------------
    void reduceEnergy(unsigned int energy);
    void reduceLife(unsigned int life);

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
};


#endif // ILLUVATAR_MINION_H
