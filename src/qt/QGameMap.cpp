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

QGameMap::QGameMap(Rectangle surface,
                   TileSet& tiles,
                   unsigned int tileSize,
                   bool showCoordinates,
                   QWidget* parent)
: QWidget(parent), surface(surface), tiles(tiles), tileSize(tileSize),
  showCoordinates(showCoordinates) { }

//  --------------------------------------------------------------------------------------
//  QGameMap > SETTERS
//  --------------------------------------------------------------------------------------

void QGameMap::setSurface(Rectangle s) {
    this->surface = s;
    this->repaint();
}

void QGameMap::setTiles(TileSet tileSet) { this->tiles = std::move(tileSet); }

[[maybe_unused]] void QGameMap::setTileSize(unsigned int size) {
    this->tileSize = size;
    this->repaint();
}

[[maybe_unused]] void QGameMap::setCoordinates(bool status) {
    if (status != this->showCoordinates) this->toggleCoordinates();
}

void QGameMap::toggleCoordinates() {
    this->showCoordinates = !this->showCoordinates;
    this->repaint();
}

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

void QGameMap::paintTile(QPainter& p, int x, int y, const QColor& fill, const QColor& border) {
    // Retrieve paint position
    auto [px, py] = this->toPaintCoordinates(Point(x, y));

    // Paint tile
    p.setPen(border);
    p.setBrush(fill);
    p.drawRect(px, py, static_cast<int>(this->tileSize), static_cast<int>(this->tileSize));

    // Show coordinates if enabled
    if (this->showCoordinates) {
        QColor color = fill.lightness() < 100 ? Qt::white : Qt::black;
        auto text =
        QString::fromStdString("(" + std::to_string(x) + ", " + std::to_string(y) + ")");

        p.setPen(color);
        p.drawText(px, py + static_cast<int>(this->tileSize), text);
    }
}

void QGameMap::paintMap(QPainter& p) {
    // Defaults
    p.setPen(Qt::black);
    p.setBrush(Qt::transparent);

    // Paint tiles
    for (int y = 0; y < this->surface.getWidth(); y++) {
        for (int x = 0; x < this->surface.getHeight(); x++) {

            if (this->tiles.exists(x, y)) {
                auto t = this->tiles.get(x, y);

                // TODO: Retrieve color from a std::map<Faction, QColor> stored somewhere
                //  this->paintTile(p, x, y, factionColor[t.getOwner()])
                switch (t.getOwner()) {
                    case Faction::Werewolves:
                        this->paintTile(p, x, y, Qt::darkGray);
                        break;
                    case Faction::Valars:
                        this->paintTile(p, x, y, Qt::cyan);
                        break;
                    case Faction::Dragons:
                        this->paintTile(p, x, y, Qt::red);
                        break;
                    case Faction::Eldars:
                        this->paintTile(p, x, y, Qt::green);
                        break;
                    case Faction::NoFaction:
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

void QGameMap::paintEvent(QPaintEvent*) {
    QPainter p(this);

    this->paintMap(p);
}
