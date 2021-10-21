/*=========================================================================

  Project:   Illuvatar
  File:      Rectangle.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_RECTANGLE_H
#define ILLUVATAR_RECTANGLE_H

/**
 * @class Rectangle
 * @brief Rectangle shape without position
 */
class Rectangle {
  public:
    /**
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    Rectangle(int width, int height);

    // - Getters -----------------------------------------------------------------------------
    /**
     * @return The width of the Rectangle
     */
    [[nodiscard]] int getWidth() const;

    /**
     * @return The height of the Rectangle
     */
    [[nodiscard]] int getHeight() const;

  private:
    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief The width of the Rectangle
     */
    int width;

    /**
     * @brief The height of the Rectangle
     */
    int height;
};

#endif // ILLUVATAR_RECTANGLE_H
