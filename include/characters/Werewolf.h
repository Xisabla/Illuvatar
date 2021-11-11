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
    Werewolf(unsigned int x, unsigned int y): BadMinion(x, y, Faction::Werewolves) { }
    
    protected:
    virtual int getDamages() { return 5; };

    virtual int getSelfDamages() { return 2; };

    virtual int getDiceMaxValue() { return 100; };

    virtual int getDiceCriticFailureValue() { return 5; };

    virtual int getDiceFailureValue() { return 50; };

    virtual int getDiceSuccessValue() { return 96; };
};


#endif // ILLUVATAR_WEREWOLF_H
