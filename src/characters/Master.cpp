/*=========================================================================

  Project:   Illuvatar
  File:      Master.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/Master.h"

//  --------------------------------------------------------------------------------------
//  Master
//  --------------------------------------------------------------------------------------

Master::Master(unsigned int x, unsigned int y, Faction faction): Character(x, y, faction) {
    // TODO: Unsure that not other master exists
}

//  --------------------------------------------------------------------------------------
//  Master > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

std::string Master::generateMessage() { return "hello world :D"; }
