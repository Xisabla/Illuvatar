/*=========================================================================

  Project:   Illuvatar
  File:      GoodMinion.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_GOODMINION_H
#define ILLUVATAR_GOODMINION_H

#include "characters/Minion.h"

/**
 * @class GoodMinion
 * @brief Short description of the class
 */
class GoodMinion : public Minion {
  public:
    GoodMinion(unsigned int x, unsigned int y, Faction faction);

    // - Methods -----------------------------------------------------------------------------

  protected:
    unsigned int energyReduction = this->energyCost * 2 / 3;

    /**
     * @brief Alliance skill : remove _energy to ennemy and attack him
     */
    virtual void specialAttack(Minion& other);
};


#endif // ILLUVATAR_GOODMINION_H
