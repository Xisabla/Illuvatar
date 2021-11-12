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
    Eldar(unsigned int x, unsigned int y): GoodMinion(x, y, Faction::Eldars) {
      nlohmann::json& env = Environment::instance()->env();

      lifeMax = env["Eldar"]["minion"]["lifeMax"];
      energyMax = env["Eldar"]["minion"]["energyMax"];
      energyLow = env["Eldar"]["minion"]["energyLow"];
      energyCost = env["Eldar"]["minion"]["energyCost"];
      energyEnnemyCost = env["Eldar"]["minion"]["energyEnnemyCost"];
      range = {env["Eldar"]["minion"]["range"]["min"], env["Eldar"]["minion"]["range"]["max"]};
      attackNature = strToAttackNature.at(env["Eldar"]["minion"]["attackNature"]);
      damages = env["Eldar"]["minion"]["damages"];
      selfDamages = env["Eldar"]["minion"]["selfDamages"];
      diceMaxValue = env["Eldar"]["minion"]["diceMaxValue"];
      diceCriticFailureValue = env["Eldar"]["minion"]["diceCriticFailureValue"];
      diceFailureValue = env["Eldar"]["minion"]["diceFailureValue"];
      diceSuccessValue = env["Eldar"]["minion"]["diceSuccessValue"];
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


#endif // ILLUVATAR_ELDAR_H
