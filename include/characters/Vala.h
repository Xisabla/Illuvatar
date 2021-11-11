/*=========================================================================

  Project:   Illuvatar
  File:      Vala.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_VALA_H
#define ILLUVATAR_VALA_H

#include "characters/GoodMinion.h"

/**
 * @class Vala
 * @brief Short description of the class
 */
class Vala : public GoodMinion {
  public:
    Vala(unsigned int x, unsigned int y): GoodMinion(x, y, Faction::Valars) { }
};


#endif // ILLUVATAR_VALA_H
