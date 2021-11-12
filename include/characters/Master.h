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

#include <vector>
#include <string>

class Minion;

/**
 * @class Master
 * @brief Short description of the class
 */
class Master : public Character {
  public:
    Master(unsigned int x, unsigned int y, Faction faction, std::vector<std::string> listOfBaseMessage);

    // - Methods -----------------------------------------------------------------------------
    std::string generateMessage();
    // TODO: void giveMessage(Mignon* minion);

    virtual std::string getAssetPath();

    void getMessage(Minion* minion);
    void giveMessage(Minion* minion);

  private:
    std::set<std::string> listOfMessage;
    std::vector<std::string> MessageToGive;
};


#endif // ILLUVATAR_MASTER_H
