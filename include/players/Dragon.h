/*=========================================================================

Project:   Illuvatar
File:      Dragon.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DRAGON_H
#define ILLUVATAR_DRAGON_H

#include "players/Horde.h"
#include "players/Master.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"

class Dragon: public Horde {
    public:
    Dragon(Map& map,
           Point point,
           Master& master);

    protected:
    unsigned int damages = 5;
    unsigned int selfDamages = 2;

    virtual int getDamages() { return this->damages; };

    virtual int getSelfDamages() { return this->selfDamages; };
};

#endif // ILLUVATAR_DRAGON_H
