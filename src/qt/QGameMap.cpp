/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "qt/QGameMap.h"

#include <utility>

//  --------------------------------------------------------------------------------------
//  QGameMap
//  --------------------------------------------------------------------------------------

QGameMap::QGameMap(Rectangle surface, QWidget* parent)
: QWidget(parent), surface(surface), tiles() { }

QGameMap::QGameMap(unsigned int width, unsigned int height, QWidget* parent)
: QGameMap(Rectangle(width, height), parent) { }

//  --------------------------------------------------------------------------------------
//  QGameMap > SETTERS
//  --------------------------------------------------------------------------------------

void QGameMap::setTiles(std::vector<Tile> tileSet) { this->tiles = std::move(tileSet); }

//  --------------------------------------------------------------------------------------
//  QGameMap > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void QGameMap::paintEvent(QPaintEvent*) {
    // TODO: Refactor: split in different private methods:
    //  - paintBackground
    //  - paintMap
    //  - paintTile
    // and helper methods:
    //  - getPaintWidth()
    //  - getPaintHeight()
    //  - getTileSize()
    //  - toPaintPosition(x, y), toPaintPosition(pos)
    // TODO: Store color mapping somewhere

    // Compute sizes
    int width = static_cast<int> (this->surface.getWidth());
    int height = static_cast<int> (this->surface.getHeight());

    int p_width = this->parentWidget()->width();
    int p_height = this->parentWidget()->height();

    int t_size =
    std::max(50, std::min(p_width, p_height) / static_cast<int>(1.1 * std::max(width, height)));
    int t_offset = std::max(static_cast<int>(p_width - (t_size * width)) / 2, 0);
    int l_offset = std::max(static_cast<int>(p_height - (t_size * height)) / 2, 0);

    // Init painter
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::transparent);

    // Paint grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            auto it = std::find_if(this->tiles.begin(), this->tiles.end(), [x, y](Tile t) {
                return t.X() == x && t.Y() == y;
            });

            if (it != this->tiles.end()) {
                Tile t = tiles[std::distance(tiles.begin(), it)];
                p.setPen(Qt::black);

                p.setBrush(Qt::white);
                if (t.belongsTo(Werewolves)) p.setBrush(Qt::gray);
                if (t.belongsTo(Valars)) p.setBrush(Qt::cyan);
                if (t.belongsTo(Dragons)) p.setBrush(Qt::red);
                if (t.belongsTo(Eldars)) p.setBrush(Qt::green);
            } else {
                p.setPen(Qt::black);
                p.setBrush(Qt::black);
            }

            p.drawRect(t_offset + x * t_size, l_offset + y * t_size, t_size, t_size);
        }
    }
}
