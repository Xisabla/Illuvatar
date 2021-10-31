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

class Horde;

class Alliance : public Minion {
    void Meet(const Horde& hordeMinion);
    void Meet(const Alliance& allianceMinion);
};

#endif // ILLUVATAR_ALLIANCE_H
