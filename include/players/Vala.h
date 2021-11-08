/*=========================================================================

Project:   Illuvatar
File:      Vala.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_VALA_H
#define ILLUVATAR_VALA_H

#include "players/Alliance.h"
#include "players/Master.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"

class Vala : public Alliance {
    public:
    Vala(Map& map,
           Point point,
           Master& master);

    protected:
    unsigned int damages = 5;
    unsigned int selfDamages = 2;

    virtual int getDamages() { return this->damages; };

    virtual int getSelfDamages() { return this->selfDamages; };
};

#endif // ILLUVATAR_VALA_H
