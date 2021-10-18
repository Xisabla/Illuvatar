/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/QGameMap.h"

//  --------------------------------------------------------------------------------------
//  QGameMap
//  --------------------------------------------------------------------------------------

QGameMap::QGameMap(int width, int height, ColoredPoints points, QWidget* parent)
: QWidget(parent), width(width), height(height), points(points) {
}

//  --------------------------------------------------------------------------------------
//  QGameMap > PRIVATE METHODS
//  --------------------------------------------------------------------------------------
void QGameMap::paintEvent(QPaintEvent*) {
    // Compute sizes
    double p_width = this->parentWidget()->width();
    double p_height = this->parentWidget()->height();

    double size = std::max(50., std::min(p_width, p_height) / (1.1 * std::max(width, height)));
    double t_offset = std::max((p_width - (size * width)) / 2, 0.);
    double l_offset = std::max((p_height - (size * height)) / 2, 0.);

    // Init painter
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::white);

    // Paint grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            p.drawRect(t_offset + x * size, l_offset + y * size, size, size);
        }
    }

    // Print colored points
    for(auto & pt: this->points) {
        Point point = pt.first;
        int x = point.getX();
        int y = point.getY();

        QColor color = pt.second;

        p.setBrush(pt.second);
        p.drawRect(t_offset + x * size, l_offset + y * size, size, size);
    }
}
