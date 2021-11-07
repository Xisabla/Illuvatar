/*=========================================================================

Project:   Illuvatar
File:      Horde.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_HORDE_H
#define ILLUVATAR_HORDE_H

#include "players/Minion.h"
#include "players/Master.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"
#include "unirand.h"

class Horde : public Minion {
    public:
    Horde(Map& map,
           Point point,
           Direction direction,
           Faction faction,
           Master& master);

    protected:
        unsigned int lifeHeal = this->lifeMax / 15;

        /**
         * @brief Horde skill : drain life to ennemy after attacking him
         */
        virtual void specialAttack(Minion& other);
};

#endif // ILLUVATAR_HORDE_H
