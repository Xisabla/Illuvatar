/*=========================================================================

  Project:   Illuvatar
  File:      BadMinion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/BadMinion.h"

//  --------------------------------------------------------------------------------------
//  BadMinion
//  --------------------------------------------------------------------------------------

BadMinion::BadMinion(unsigned int x, unsigned int y, Faction faction): Minion(x, y, faction) { }

//  --------------------------------------------------------------------------------------
//  BadMinion > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void BadMinion::meet(BadMinion* minion) { }

void BadMinion::meet(GoodMinion* minion) { }
