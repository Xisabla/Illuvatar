/*=========================================================================

  Project:   Illuvatar
  File:      BadMinion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/BadMinion.h"
#include "unirand.h"

//  --------------------------------------------------------------------------------------
//  BadMinion
//  --------------------------------------------------------------------------------------

BadMinion::BadMinion(unsigned int x, unsigned int y, Faction faction): Minion(x, y, faction) { }

//  --------------------------------------------------------------------------------------
//  BadMinion > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void BadMinion::specialAttack(Minion* minion) {
    this->normalAttack(minion);
    this->restoreLife(unirand::getValueAround(this->lifeHeal, 2));
}
