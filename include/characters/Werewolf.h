/*=========================================================================

  Project:   Illuvatar
  File:      Werewolf.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_WEREWOLF_H
#define ILLUVATAR_WEREWOLF_H

#include "characters/BadMinion.h"
#include "enums/AttackNature.h"
#include "core/Environment.h"
#include "libs/json.h"

/**
 * @class Werewolf
 * @brief Short description of the class
 */
class Werewolf : public BadMinion {
  public:
    Werewolf(unsigned int x, unsigned int y): BadMinion(x, y, Faction::Werewolves) {
      nlohmann::json& env = Environment::instance()->env();

      lifeMax = env["Werewolf"]["minion"]["lifeMax"];
      energyMax = env["Werewolf"]["minion"]["energyMax"];
      energyLow = env["Werewolf"]["minion"]["energyLow"];
      energyCost = env["Werewolf"]["minion"]["energyCost"];
      energyEnnemyCost = env["Werewolf"]["minion"]["energyEnnemyCost"];
      range = {env["Werewolf"]["minion"]["range"]["min"], env["Werewolf"]["minion"]["range"]["max"]};
      attackNature = strToAttackNature.at(env["Werewolf"]["minion"]["attackNature"]);
      damages = env["Werewolf"]["minion"]["damages"];
      selfDamages = env["Werewolf"]["minion"]["selfDamages"];
      diceMaxValue = env["Werewolf"]["minion"]["diceMaxValue"];
      diceCriticFailureValue = env["Werewolf"]["minion"]["diceCriticFailureValue"];
      diceFailureValue = env["Werewolf"]["minion"]["diceFailureValue"];
      diceSuccessValue = env["Werewolf"]["minion"]["diceSuccessValue"];
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


#endif // ILLUVATAR_WEREWOLF_H
