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

Rectangle::Rectangle(int width, int height): width(width), height(height) { }

//  --------------------------------------------------------------------------------------
//  Rectangle > GETTERS
//  --------------------------------------------------------------------------------------

int Rectangle::getWidth() const { return this->width; }

int Rectangle::getHeight() const { return this->height; }
