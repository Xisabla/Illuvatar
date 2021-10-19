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
//  QGameMap > SETTERS
//  --------------------------------------------------------------------------------------
void QGameMap::setPointColor(Point p, QColor color) {
    if (std::find(this->points.begin(), this->points.end(), std::make_pair(p, color)) == this->points.end())
        this->points.emplace_back(p, color);
}

void QGameMap::setPoints(ColoredPoints points) {
    this->points = points;
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
        int x = point.X();
        int y = point.Y();

        QColor color = pt.second;

        p.setBrush(color);
        p.drawRect(t_offset + x * size, l_offset + y * size, size, size);
    }
}
