/*=========================================================================

  Project:   Illuvatar
  File:      GoodMinion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/GoodMinion.h"
#include "unirand.h"

//  --------------------------------------------------------------------------------------
//  GoodMinion
//  --------------------------------------------------------------------------------------

GoodMinion::GoodMinion(unsigned int x, unsigned int y, Faction faction): Minion(x, y, faction) { }

//  --------------------------------------------------------------------------------------
//  GoodMinion > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void GoodMinion::specialAttack(Minion& other) {
    other.reduceEnergy(unirand::getValueAround(this->energyReduction, 2));
    this->normalAttack(other);
}
