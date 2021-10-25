/*=========================================================================

  Project:   Illuvatar
  File:      Master.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_MASTER_H
#define ILLUVATAR_MASTER_H

#include "model/abstract/Character.h"
#include "model/abstract/Minion.h"

class Master : public Character {
  public:
    Faction faction;

    std::string GetMessage(Minion& minion);
    void GiveMessage(Minion& minion);
};


#endif // ILLUVATAR_MASTER_H
