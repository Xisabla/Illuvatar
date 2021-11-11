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
#include "characters/BadMinion.h"

class BadMinion;

/**
 * @class GoodMinion
 * @brief Short description of the class
 */
class GoodMinion : public Minion {
  public:
    GoodMinion(unsigned int x, unsigned int y, Faction faction /*, Direction direction = DEFAULT */);

    // - Methods -----------------------------------------------------------------------------
    // TODO ? Set method as virtual is Minion.h
    void meet(BadMinion* minion);
    void meet(GoodMinion* minion);
};


#endif // ILLUVATAR_GOODMINION_H
