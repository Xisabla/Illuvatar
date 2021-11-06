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
           Direction direction,
           Faction faction,
           Master& master);
};

#endif // ILLUVATAR_WEREWOLF_H
