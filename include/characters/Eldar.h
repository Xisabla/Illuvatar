/*=========================================================================

  Project:   Illuvatar
  File:      Eldar.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_ELDAR_H
#define ILLUVATAR_ELDAR_H

#include "characters/GoodMinion.h"

/**
 * @class Eldar
 * @brief Short description of the class
 */
class Eldar : public GoodMinion {
  public:
    Eldar(unsigned int x, unsigned int y): GoodMinion(x, y, Eldars) { }
};


#endif // ILLUVATAR_ELDAR_H
