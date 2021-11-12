/*=========================================================================

  Project:   Illuvatar
  File:      Dragon.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DRAGON_H
#define ILLUVATAR_DRAGON_H

#include "characters/BadMinion.h"
#include "enums/AttackNature.h"
#include "core/Environment.h"
#include "libs/json.h"

/**
 * @class Dragon
 * @brief Short description of the class
 */
class Dragon : public BadMinion {
  public:
    Dragon(unsigned int x, unsigned int y): BadMinion(x, y, Faction::Dragons) {
      auto minions = Environment::instance()->env()["characters"]["Dragon"]["minion"];

      lifeMax = minions["lifeMax"];
      energyMax = minions["energyMax"];
      energyLow = minions["energyLow"];
      energyCost = minions["energyCost"];
      energyEnnemyCost = minions["energyEnnemyCost"];
      range = {minions["range"]["min"], minions["range"]["max"]};
      attackNature = strToAttackNature.at(minions["attackNature"]);
      damages = minions["damages"];
      selfDamages = minions["selfDamages"];
      diceMaxValue = minions["diceMaxValue"];
      diceCriticFailureValue = minions["diceCriticFailureValue"];
      diceFailureValue = minions["diceFailureValue"];
      diceSuccessValue = minions["diceSuccessValue"];
    }

  protected:
    int lifeMax;
    int energyMax;
    int energyLow;
    int energyCost;
    int energyEnnemyCost;
    std::pair<int, int> range;
    AttackNature attackNature;
    int damages;
    int selfDamages;
    int diceMaxValue;
    int diceCriticFailureValue;
    int diceFailureValue;
    int diceSuccessValue;

    virtual int getLifeMax() { return lifeMax; };

    virtual int getEnergyMax() { return energyMax; };
    virtual int getEnergyLow() { return energyLow; };
    virtual int getEnergyCost() { return energyCost; };
    virtual int getEnergyEnnemyCost() { return energyEnnemyCost; };
    virtual std::pair<int, int> getRange() { return range; };

    virtual AttackNature getAttackNature() { return attackNature; };
    virtual int getDamages() { return damages; };
    virtual int getSelfDamages() { return selfDamages; };

    virtual int getDiceMaxValue() { return diceMaxValue; };
    virtual int getDiceCriticFailureValue() { return diceCriticFailureValue; };
    virtual int getDiceFailureValue() { return diceFailureValue; };
    virtual int getDiceSuccessValue() { return diceSuccessValue; };
};

#endif // ILLUVATAR_DRAGON_H
