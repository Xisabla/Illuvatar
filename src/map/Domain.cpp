/*=========================================================================

  Project:   Illuvatar
  File:      Domain.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Domain.h"

//  --------------------------------------------------------------------------------------
//  Domain
//  --------------------------------------------------------------------------------------

Domain::Domain(const unsigned int width, const unsigned int height)
: _width(width), _height(height) { }

//  --------------------------------------------------------------------------------------
//  Domain > GETTERS
//  --------------------------------------------------------------------------------------

unsigned int Domain::width() const { return _width; }

unsigned int Domain::height() const { return _height; }
