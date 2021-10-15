/*=========================================================================

  Project:   Illuvatar
  File:      Map.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

#include "map/map.h"


//  --------------------------------------------------------------------------------------
//  Map
//  --------------------------------------------------------------------------------------
Map::Map(int width, int height, QWidget* parent): QWidget(parent), width(width), height(height) {
    this->repaint();
}

//  --------------------------------------------------------------------------------------
//  Map > GETTERS
//  --------------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------------
//  Map > SETTERS
//  --------------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------------
//  Map > PRIVATE METHODS
//  --------------------------------------------------------------------------------------
void Map::paintEvent(QPaintEvent* event) {
    double size = 50;
    double t_offset = std::max((this->parentWidget()->width() - (size * width)) / 2, 0.);
    double l_offset = std::max((this->parentWidget()->height() - (size * height)) / 2, 0.);

    std::vector<QBrush> colors = { Qt::red, Qt::green };
    size_t current_color = 0;

    QPainter p(this);
    p.setPen(Qt::black);

    // Print map
    for (int y = 0; y < height; y++) {
        current_color = (y % colors.size());
        for (int x = 0; x < width; x++) {
            ++current_color %= colors.size();

            p.setBrush(colors[current_color]);
            p.drawRect(t_offset + x * size, l_offset + y * size, size, size);
        }
    }
}
