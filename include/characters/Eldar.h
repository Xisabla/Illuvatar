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
#include "enums/AttackNature.h"
#include "core/Environment.h"
#include "libs/json.h"

/**
 * @class Eldar
 * @brief Short description of the class
 */
class Eldar : public GoodMinion {
  public:
    Eldar(unsigned int x, unsigned int y): GoodMinion(x, y, Faction::Eldars) {
      auto minions = Environment::instance()->env()["characters"]["Eldar"]["minion"];

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
      id = Eldar::counter++;
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

#ifndef ILLUVATAR_ELDAR_COUNTER
#define ILLUVATAR_ELDAR_COUNTER

unsigned int Eldar::counter = 0;

#endif // ILLUVATAR_ELDAR_COUNTER

#endif // ILLUVATAR_ELDAR_H
