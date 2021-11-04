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
           Direction direction,
           Faction faction,
           Master& master);
};

#endif // ILLUVATAR_VALA_H
