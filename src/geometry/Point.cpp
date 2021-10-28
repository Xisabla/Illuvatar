/*=========================================================================

  Project:   Illuvatar
  File:      Point.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "geometry/Point.h"

//  --------------------------------------------------------------------------------------
//  Point
//  --------------------------------------------------------------------------------------

Point::Point(int x, int y): x(x), y(y) { }

//  --------------------------------------------------------------------------------------
//  Point > GETTERS
//  --------------------------------------------------------------------------------------

int Point::X() const { return x; }

int Point::Y() const { return y; }

Point Point::getPoint() { return Point(x, y); }