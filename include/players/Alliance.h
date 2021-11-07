/*=========================================================================

Project:   Illuvatar
File:      Alliance.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_ALLIANCE_H
#define ILLUVATAR_ALLIANCE_H

#include "players/Minion.h"
#include "players/Master.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"
#include "unirand.h"

class Alliance : public Minion {
    public:
        Alliance(Map& map,
            Point point,
            Direction direction,
            Faction faction,
            Master& master);

    protected:
        unsigned int energyReduction = this->energyCost * 2 / 3;

        /**
         * @brief Alliance skill : remove energy to ennemy and attack him
         */
        virtual void specialAttack(Minion& other);
};

#endif // ILLUVATAR_ALLIANCE_H
