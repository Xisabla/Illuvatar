/*=========================================================================

  Project:   Illuvatar
  File:      Rectangle.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "geometry/Rectangle.h"

//  --------------------------------------------------------------------------------------
//  Rectangle
//  --------------------------------------------------------------------------------------

Rectangle::Rectangle(unsigned int width, unsigned int height): width(width), height(height) { }

//  --------------------------------------------------------------------------------------
//  Rectangle > GETTERS
//  --------------------------------------------------------------------------------------

unsigned int Rectangle::getWidth() const { return this->width; }

unsigned int Rectangle::getHeight() const { return this->height; }
