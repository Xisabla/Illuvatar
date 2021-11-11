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
#include "enums/Faction.h"

#include <string>

/**
 * @class Master
 * @brief Short description of the class
 */
class Master : public Character {
  public:
    Master(unsigned int x, unsigned int y, Faction faction);

    // - Methods -----------------------------------------------------------------------------
    std::string generateMessage();
    // TODO: void giveMessage(Mignon* minion);

    virtual std::string getAssetPath();
};


#endif // ILLUVATAR_MASTER_H
