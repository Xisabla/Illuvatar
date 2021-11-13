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
      auto minions = Environment::instance()->env()["characters"]["Werewolf"]["minion"];

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
      id = Werewolf::counter++;
    }

  protected:
    static unsigned int counter;
    unsigned int id;

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

    virtual unsigned int getId() { return id; }

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

#ifndef ILLUVATAR_WEREWOLF_COUNTER
#define ILLUVATAR_WEREWOLF_COUNTER

unsigned int Werewolf::counter = 0;

#endif // ILLUVATAR_WEREWOLF_COUNTER

#endif // ILLUVATAR_WEREWOLF_H
