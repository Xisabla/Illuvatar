/*=========================================================================

  Project:   Illuvatar
  File:      Werewolf.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_WEREWOLF_H
#define ILLUVATAR_WEREWOLF_H

#include "characters/BadMinion.h"

/**
 * @class Werewolf
 * @brief Short description of the class
 */
class Werewolf : public BadMinion {
  public:
    Werewolf(unsigned int x, unsigned int y): BadMinion(x, y, Werewolves) { }
};


#endif // ILLUVATAR_WEREWOLF_H
