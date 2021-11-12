/*=========================================================================

  Project:   Illuvatar
  File:      Vala.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_VALA_H
#define ILLUVATAR_VALA_H

#include "characters/GoodMinion.h"
#include "enums/AttackNature.h"
#include "core/Environment.h"
#include "libs/json.h"

/**
 * @class Vala
 * @brief Short description of the class
 */
class Vala : public GoodMinion {
  public:
    Vala(unsigned int x, unsigned int y): GoodMinion(x, y, Faction::Valars) {
      nlohmann::json& env = Environment::instance()->env();

      lifeMax = env["Vala"]["minion"]["lifeMax"];
      energyMax = env["Vala"]["minion"]["energyMax"];
      energyLow = env["Vala"]["minion"]["energyLow"];
      energyCost = env["Vala"]["minion"]["energyCost"];
      energyEnnemyCost = env["Vala"]["minion"]["energyEnnemyCost"];
      range = {env["Vala"]["minion"]["range"]["min"], env["Vala"]["minion"]["range"]["max"]};
      attackNature = strToAttackNature.at(env["Vala"]["minion"]["attackNature"]);
      damages = env["Vala"]["minion"]["damages"];
      selfDamages = env["Vala"]["minion"]["selfDamages"];
      diceMaxValue = env["Vala"]["minion"]["diceMaxValue"];
      diceCriticFailureValue = env["Vala"]["minion"]["diceCriticFailureValue"];
      diceFailureValue = env["Vala"]["minion"]["diceFailureValue"];
      diceSuccessValue = env["Vala"]["minion"]["diceSuccessValue"];
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


#endif // ILLUVATAR_VALA_H
