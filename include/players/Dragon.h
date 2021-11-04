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
           Direction direction,
           Faction faction,
           Master& master);
 };

#endif // ILLUVATAR_DRAGON_H
