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
#include "map/TileSet.h"

#include <QPainter>
#include <QWidget>

#ifdef DEBUG
#define DEFAULT_QGAMEMAP_SHOW_COORDINATES true
#else
#define DEFAULT_QGAMEMAP_SHOW_COORDINATES false
#endif

// TODO: Better size handling on a settings tab:
//  - Tile size (min, max, auto: true/false/mixed)
//  - Default constants
//  - Store those settings (use of Toml++ ?)
// TODO: Debug mode with coordinates

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
    QGameMap(unsigned int width, unsigned int height, QWidget* parent = nullptr);

    // - Setters -----------------------------------------------------------------------------
    /**
     * Set the tiles of the widget
     */
    void setTiles(TileSet tileSet);

  private:
    // - Methods -----------------------------------------------------------------------------
    std::pair<int, int> toPaintCoordinates(Point p);
    void paintTile(QPainter& p, int x, int y, QColor fill = Qt::black, QColor border = Qt::black);

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
    TileSet tiles;


    // TODO: Initialize in constructor + getters/setters --> repaint
    int tileSize = 50;
    bool showCoordinates = DEFAULT_QGAMEMAP_SHOW_COORDINATES;
};

#endif // ILLUVATAR_QGAMEMAP_H
