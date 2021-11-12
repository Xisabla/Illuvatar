/*=========================================================================

  Project:   Illuvatar
  File:      Master.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MASTER_H
#define ILLUVATAR_MASTER_H

#include "characters/Character.h"
#include "characters/Minion.h"
#include "enums/Faction.h"
#include "core/Environment.h"
#include "unirand.h"

#include <vector>
#include <string>

class Minion;

/**
 * @class Master
 * @brief Short description of the class
 */
class Master : public Character {
  public:
    Master(unsigned int x, unsigned int y, Faction faction);

    // - Methods -----------------------------------------------------------------------------

    virtual std::string getAssetPath();

    void collectAndSendBack(Minion* minion);
    // void getMessage(Minion* minion);
    // void giveMessage(Minion* minion);

  private:
    virtual void addMessages(std::vector<std::string> messages);
    virtual std::string getRandomMessage();

    std::vector<std::string> messagesFaction;
};


#endif // ILLUVATAR_MASTER_H
