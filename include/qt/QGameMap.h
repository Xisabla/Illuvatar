/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_QGAMEMAP_H
#define ILLUVATAR_QGAMEMAP_H

#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "map/Tile.h"

#include <QPainter>
#include <QWidget>

// TODO: Better size handling on a settings tab:
//  - Tile size (min, max, auto: true/false/mixed)
//  - Default constants
//  - Store those settings (use of Toml++ ?)

/**
 * @class QGameMap
 * @brief Qt Widget that shows the map
 */
class QGameMap : public QWidget {
  public:
    /**
     * @param surface Map rectangular shape
     * @param parent Qt parent widget
     */
    explicit QGameMap(Rectangle surface, QWidget* parent = nullptr);

    /**
     * @param width Map width (in tiles)
     * @param height Map height (in tiles)
     * @param parent Qt parent widget
     */
    QGameMap(int width, int height, QWidget* parent = nullptr);

    // - Setters -----------------------------------------------------------------------------
    /**
     * Set the tiles of the widget
     */
    void setTiles(std::vector<Tile> tileSet);

  private:
    // - Methods -----------------------------------------------------------------------------
    /**
     * Paint the map on the widget using QPainter
     */
    void paintEvent(QPaintEvent*) override;

    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Map rectangular shape
     */
    Rectangle surface;

    /**
     * @brief Available Tiles on the map
     */
    std::vector<Tile> tiles;
};

#endif // ILLUVATAR_QGAMEMAP_H