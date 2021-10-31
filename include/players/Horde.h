/*=========================================================================

Project:   Illuvatar
File:      Horde.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_HORDE_H
#define ILLUVATAR_HORDE_H

#include "players/Alliance.h"
#include "players/Minion.h"

class Alliance;

class Horde : public Minion {
    void Meet(const Horde& hordeMinion);
    void Meet(const Alliance& allianceMinion);
};

#endif // ILLUVATAR_HORDE_H
