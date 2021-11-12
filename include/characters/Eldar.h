/*=========================================================================

  Project:   Illuvatar
  File:      Eldar.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_ELDAR_H
#define ILLUVATAR_ELDAR_H

#include "characters/GoodMinion.h"

/**
 * @class Eldar
 * @brief Short description of the class
 */
class Eldar : public GoodMinion {
  public:
    Eldar(unsigned int x, unsigned int y): GoodMinion(x, y, Faction::Eldars) { }
    
    protected:
    virtual int getLifeMax() { return 100; };

    virtual int getEnergyMax() { return 100; };
    virtual int getEnergyLow() { return 20; };
    virtual int getEnergyCost() { return 5; };
    virtual int getEnergyEnnemyCost() { return 10; };
    virtual std::pair<int, int> getRange() { return { 6, 10 }; };

    virtual AttackNature getAttackNature() { return AttackNature::Physical; };
    virtual int getDamages() { return 5; };
    virtual int getSelfDamages() { return 2; };

    virtual int getDiceMaxValue() { return 100; };
    virtual int getDiceCriticFailureValue() { return 5; };
    virtual int getDiceFailureValue() { return 50; };
    virtual int getDiceSuccessValue() { return 96; };
};


#endif // ILLUVATAR_ELDAR_H
