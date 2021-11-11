/*=========================================================================

  Project:   Illuvatar
  File:      BadMinion.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_BADMINION_H
#define ILLUVATAR_BADMINION_H

#include "characters/Minion.h"

/**
 * @class BadMinion
 * @brief Short description of the class
 */
class BadMinion : public Minion {
  public:
    BadMinion(unsigned int x, unsigned int y, Faction faction /*, Direction direction = DEFAULT */);

    // - Methods -----------------------------------------------------------------------------

  protected:
    unsigned int lifeHeal = this->_lifeMax / 15;

    /**
     * @brief Horde skill : drain life to ennemy after attacking him
     */
    virtual void specialAttack(Minion& other);
};


#endif // ILLUVATAR_BADMINION_H
