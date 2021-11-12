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
      nlohmann::json& env = Environment::instance()->env();

      lifeMax = env["Dragon"]["minion"]["lifeMax"];
      energyMax = env["Dragon"]["minion"]["energyMax"];
      energyLow = env["Dragon"]["minion"]["energyLow"];
      energyCost = env["Dragon"]["minion"]["energyCost"];
      energyEnnemyCost = env["Dragon"]["minion"]["energyEnnemyCost"];
      range = {env["Dragon"]["minion"]["range"]["min"], env["Dragon"]["minion"]["range"]["max"]};
      attackNature = strToAttackNature.at(env["Dragon"]["minion"]["attackNature"]);
      damages = env["Dragon"]["minion"]["damages"];
      selfDamages = env["Dragon"]["minion"]["selfDamages"];
      diceMaxValue = env["Dragon"]["minion"]["diceMaxValue"];
      diceCriticFailureValue = env["Dragon"]["minion"]["diceCriticFailureValue"];
      diceFailureValue = env["Dragon"]["minion"]["diceFailureValue"];
      diceSuccessValue = env["Dragon"]["minion"]["diceSuccessValue"];
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
