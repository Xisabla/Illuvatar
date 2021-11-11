/*=========================================================================

  Project:   Illuvatar
  File:      Dragon.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DRAGON_H
#define ILLUVATAR_DRAGON_H

#include "characters/BadMinion.h"

/**
 * @class Dragon
 * @brief Short description of the class
 */
class Dragon : public BadMinion {
  public:
    Dragon(unsigned int x, unsigned int y): BadMinion(x, y, Faction::Dragons) { }
};


#endif // ILLUVATAR_DRAGON_H
