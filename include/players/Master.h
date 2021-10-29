/*=========================================================================

  Project:   Illuvatar
  File:      Master.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_MASTER_H
#define ILLUVATAR_MASTER_H

#include "players/Character.h"
#include "Players/Minion.h"

class Minion;

class Master : public Character {
  public:
    Faction faction;

    std::string GetMessage(Minion& minion);
    void GiveMessage(Minion& minion);
};


#endif // ILLUVATAR_MASTER_H
