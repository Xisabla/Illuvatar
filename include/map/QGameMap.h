/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_QGAMEMAP_H
#define ILLUVATAR_QGAMEMAP_H

#include "map/Point.h"

#include <QPainter>
#include <QWidget>
#include <iostream>
#include <map>

using ColoredPoints = std::vector<std::pair<Point, QColor>>;

/**
 * @class QGameMap
 * @brief Qt Widget to paint the map on
 */
class QGameMap : public QWidget {
  public:
    /**
     * @param width Width of the map (number of tiles)
     * @param height Height of the map (number of tiles)
     * @param points Special points (tiles) to show with specific colors
     * @param parent Parent Qt Widget (facultative)
     */
    QGameMap(int width, int height, ColoredPoints points = {}, QWidget* parent = nullptr);

    // - Setters -----------------------------------------------------------------------------
    /**
     * Set the color of a specific point (tile)
     * @param p Point to set the color
     * @param color Color to set the point to
     */
    void setPointColor(Point p, QColor color);

    /**
     * Overwrite the list of special points
     * @param points Points to overwrite the list with
     */
    void setPoints(ColoredPoints points);

  private:
    // - Methods -----------------------------------------------------------------------------
    void paintEvent(QPaintEvent*) override;
    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Width of the map (number of tiles)
     */
    int width;

    /**
     * @brief Height of the map (number of tiles)
     */
    int height;

    /**
     * @brief Special points (tiles) to show with specific colors
     */
    ColoredPoints points;
};

#endif // ILLUVATAR_QGAMEMAP_H
