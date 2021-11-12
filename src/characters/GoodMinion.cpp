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

void GoodMinion::specialAttack(Minion* minion) {
    minion->reduceEnergy(unirand::getValueAround(this->getEnergyReduction(), 2));
    this->normalAttack(minion);
}
