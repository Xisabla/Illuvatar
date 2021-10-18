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
 * @brief Qt Widget to handle map drawing
 */
class QGameMap : public QWidget {
  public:
    QGameMap(int width, int height, ColoredPoints points = {}, QWidget* parent = 0);

  private:
    // - Methods -----------------------------------------------------------------------------
    void paintEvent(QPaintEvent*);

    // - Attributes --------------------------------------------------------------------------
    int width, height;
    ColoredPoints points;
};

#endif // ILLUVATAR_QGAMEMAP_H
