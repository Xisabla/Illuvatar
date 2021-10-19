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
    /**
     * @param x X coordinate of the point
     * @param y Y coordinate of the point
     */
    Point(int x, int y);

    // - Getters -----------------------------------------------------------------------------
    /**
     * @return The X coordinate of the point
     */
    int X();

    /**
     * @return The Y coordinate of the point
     */
    int Y();

    // - Operators ---------------------------------------------------------------------------
    /**
     * @param p Point to test equality with
     * @return True if the current point is the same as the given point
     */
    inline bool operator==(const Point& p) const { return x == p.x && y == p.y; }

  private:
    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief X coordinate of the point
     */
    int x;

    /**
     * @brief Y coordinate of the point
     */
    int y;
};

#endif // ILLUVATAR_POINT_H
