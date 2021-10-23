/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "qt/QGameMap.h"

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

void QGameMap::setTiles(TileSet tileSet) { this->tiles = std::move(tileSet); }

//  --------------------------------------------------------------------------------------
//  QGameMap > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

std::pair<int, int> QGameMap::toPaintCoordinates(Point p) {
    int width = static_cast<int>(this->surface.getWidth());
    int height = static_cast<int>(this->surface.getHeight());

    int p_width = this->parentWidget()->width();
    int p_height = this->parentWidget()->height();

    int t_offset = std::max(static_cast<int>(p_width - (this->tileSize * width)) / 2, 0);
    int l_offset = std::max(static_cast<int>(p_height - (this->tileSize * height)) / 2, 0);

    return std::make_pair(t_offset + p.X() * this->tileSize, l_offset + p.Y() * this->tileSize);
}

void QGameMap::paintTile(QPainter& p, int x, int y, QColor fill, QColor border) {
    // Retrieve paint position
    auto [px, py] = this->toPaintCoordinates(Point(x, y));

    // Paint tile
    p.setPen(border);
    p.setBrush(fill);
    p.drawRect(px, py, this->tileSize, this->tileSize);

    // Show coordinates if enabled
    if (this->showCoordinates)
        p.drawText(
        px, py, QString::fromStdString("(" + std::to_string(x) + ", " + std::to_string(y) + ")"));
}

void QGameMap::paintEvent(QPaintEvent*) {
    // TODO: Refactor: split in different private methods:
    //  - paintBackground
    //  - paintMap
    //  and helper methods:
    //  - getPaintWidth()
    //  - getPaintHeight()

    // Init painter
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::transparent);

    // Paint grid
    for (int y = 0; y < this->surface.getWidth(); y++) {
        for (int x = 0; x < this->surface.getHeight(); x++) {

            if (this->tiles.exists(x, y)) {
                auto t = this->tiles.get(x, y);

                // TODO: Retrieve color from a std::map<Faction, QColor> stored somewhere
                //  this->paintTile(p, x, y, factionColor[t.getOwner()])
                switch (t.getOwner()) {
                    case Werewolves:
                        this->paintTile(p, x, y, Qt::gray);
                        break;
                    case Valars:
                        this->paintTile(p, x, y, Qt::cyan);
                        break;
                    case Dragons:
                        this->paintTile(p, x, y, Qt::red);
                        break;
                    case Eldars:
                        this->paintTile(p, x, y, Qt::green);
                        break;
                    case NoFaction:
                    default:
                        this->paintTile(p, x, y, Qt::white);
                        break;
                }
            } else {
                this->paintTile(p, x, y);
            }
        }
    }
}
