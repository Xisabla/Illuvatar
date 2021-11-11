/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "gui/QGameMap.h"

#include "map/Map.h"

#include <QPainter>
#include <iostream>

//  --------------------------------------------------------------------------------------
//  QGameMap
//  --------------------------------------------------------------------------------------

QGameMap::QGameMap(QWidget* parent): QWidget(parent) { }

//  --------------------------------------------------------------------------------------
//  QGameMap > GETTERS
//  --------------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------------
//  QGameMap > SETTERS
//  --------------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------------
//  QGameMap > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

//  --------------------------------------------------------------------------------------
//  QGameMap > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void QGameMap::paintEvent(QPaintEvent*) {
    QPainter p(this);

    // Compute sizes
    int nTiles = static_cast<int>(std::max(Map::instance().width(), Map::instance().height()));
    int space = std::min(width(), height());
    int size = static_cast<int>(space / nTiles);

    // Map
    Map& map = Map::instance();

    // TODO: Togglers:
    //  - Show coordinates (on the side, chess like)
    //  - Show tiles borders

    // TODO: Refacto/Split
    for (int x = 0; x < map.width(); x++) {
        for (int y = 0; y < map.height(); y++) {
            p.setPen(Qt::white);
            p.setBrush(Qt::black);

            if (Tile::exists(x, y)) {
                p.setBrush(Qt::white);
                p.setPen(Qt::black);

                auto t = Tile::get(x, y);

                // todo : map owner - color
                if (t->isOwnedBy(Faction::Dragons)) p.setBrush(Qt::red);
                if (t->isOwnedBy(Faction::Eldars)) p.setBrush(Qt::green);
                if (t->isOwnedBy(Faction::Valars)) p.setBrush(Qt::cyan);
                if (t->isOwnedBy(Faction::Werewolves)) p.setBrush(Qt::darkGray);

                p.drawRect(x * size, y * size, size, size);

                if (map.containsCharacter(x, y)) {
                    QImage asset = QImage(("../assets/"+map.getCharacter(x, y)->getAsset()).c_str());

                    p.drawImage(x * size, y * size, asset.scaled(size, size));
                }
            } else {
                p.drawRect(x * size, y * size, size, size);
            }
        }
    }
}
