/*=========================================================================

Project:   Illuvatar
File:      Werewolf.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_WEREWOLF_H
#define ILLUVATAR_WEREWOLF_H

#include "players/Horde.h"
#include "players/Master.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"

class Werewolf: public Horde {
    public:
    Werewolf(Map& map,
           Point point,
           Master& master);

    protected:
      unsigned int damages = 3;
      unsigned int selfDamages = 2;

      virtual int getDamages() { return this->damages; };

      virtual int getSelfDamages() { return this->selfDamages; };

      virtual int getDiceMaxValue() { return 100; };

      virtual int getDiceCriticFailureValue() { return 3; };

      virtual int getDiceFailureValue() { return 25; };

      virtual int getDiceSuccessValue() { return 91; };
};

#endif // ILLUVATAR_WEREWOLF_H
