/*=========================================================================

  Project:   Illuvatar
  File:      Point.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_POINT_H
#define ILLUVATAR_POINT_H

/**
 * @class Point
 * @brief Representation of a point on the map
 */
class Point {
  public:
    Point(int x, int y);

    // - Getters -----------------------------------------------------------------------------
    int getX();
    int getY();

    // - Operators ---------------------------------------------------------------------------
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }

  private:
    // - Attributes --------------------------------------------------------------------------
    int x, y;
};

#endif // ILLUVATAR_POINT_H
