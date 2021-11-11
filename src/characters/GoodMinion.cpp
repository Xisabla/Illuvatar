/*=========================================================================

  Project:   Illuvatar
  File:      GoodMinion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/GoodMinion.h"

//  --------------------------------------------------------------------------------------
//  GoodMinion
//  --------------------------------------------------------------------------------------

GoodMinion::GoodMinion(unsigned int x, unsigned int y, Faction faction): Minion(x, y, faction) { }

//  --------------------------------------------------------------------------------------
//  GoodMinion > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void GoodMinion::meet(BadMinion* minion) { }

void GoodMinion::meet(GoodMinion* minion) { }
