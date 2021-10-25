/*=========================================================================

Project:   Illuvatar
File:      Alliance.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_ALLIANCE_H
#define ILLUVATAR_ALLIANCE_H

#include "Horde.h"

class Alliance {
    void Meet(Horde hordeMinion);
    void Meet(Alliance allianceMinion);
};


#endif // ILLUVATAR_ALLIANCE_H
