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
#include "players/Minion.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"
#include "unirand.h"

class Vala : public Alliance {
    public:
    Vala(Map& map,
           Point point,
           Direction direction,
           Faction faction,
           Master& master);

    protected:
    unsigned int damages = 5;
    unsigned int selfDamages = 2;

    /**
     * @brief Inflict life or energy damages to other Minion
     */
    virtual void normalAttack(Minion& other);
    
    /**
     * @brief Inflict life or energy damages to itself
     */
    virtual void hurtItself();
};

#endif // ILLUVATAR_VALA_H
