/*=========================================================================

Project:   Illuvatar
File:      Horde.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_HORDE_H
#define ILLUVATAR_HORDE_H

#include "Alliance.h"
#include "Minion.h"

class Horde : public Minion {
    void Meet(Horde hordeMinion);
    void Meet(Alliance allianceMinion);
};

#endif // ILLUVATAR_HORDE_H
