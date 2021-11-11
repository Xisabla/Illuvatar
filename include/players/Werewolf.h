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
           Master& master): Horde(map, point, Faction::Werewolves, master) {}

    protected:
    unsigned int damages = 5;
    unsigned int selfDamages = 2;

    virtual int getDamages() { return this->damages; };

    virtual int getSelfDamages() { return this->selfDamages; };

    virtual int getDiceMaxValue() { return 100; };

    virtual int getDiceCriticFailureValue() { return 5; };

    virtual int getDiceFailureValue() { return 50; };

    virtual int getDiceSuccessValue() { return 96; };
};

#endif // ILLUVATAR_WEREWOLF_H
