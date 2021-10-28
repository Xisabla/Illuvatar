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
    [[nodiscard]] int X() const;

    /**
     * @return The Y coordinate of the point
     */
    [[nodiscard]] int Y() const;

    // - Operators ---------------------------------------------------------------------------
    inline bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    
    inline bool operator<(const Point& p) const { return x < p.x || y < p.y; }

  protected:
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
