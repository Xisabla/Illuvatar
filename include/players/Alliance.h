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
#include "players/Horde.h"
#include "players/Master.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "geometry/Point.h"
#include "map/Map.h"

class Horde;

class Alliance : public Minion {
    public:
    Alliance(Map& map,
           Point point,
           Direction direction,
           Faction faction,
           Master& master);

    void Meet(const Horde& hordeMinion);
    void Meet(const Alliance& allianceMinion);
};

#endif // ILLUVATAR_ALLIANCE_H
