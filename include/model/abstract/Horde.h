//
// Created by ychixm on 15/10/2021.
//

#ifndef ILLUVATAR_HORDE_H
#define ILLUVATAR_HORDE_H

#include "Minion.h"
#include "Alliance.h"

class Horde : public Minion
{
    void Meet(Horde hordeMinion);
    void Meet(Alliance allianceMinion);
};


#endif // ILLUVATAR_HORDE_H
