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
#include <iostream>

#ifdef DEBUG
#define DEFAULT_QGAMEMAP_SHOW_COORDINATES true
#else
#define DEFAULT_QGAMEMAP_SHOW_COORDINATES false
#endif

// TODO: Better size handling on a settings tab:
//  - Tile size (min, max, auto: true/false/mixed)
//  - Store those settings (use of Toml++ ?)

/**
 * @class QGameMap
 * @brief Qt Widget that shows the map
 */
class QGameMap : public QWidget {
  public:
    /**
     * @param surface Map rectangular shape
     * @param tileSize Size of Tile on the Widget
     * @param showCoordinates If set on true, will show coordinates of Tiles
     * @param parent Qt parent widget
     */
    explicit QGameMap(Rectangle surface,
                      TileSet& tiles,
                      unsigned int tileSize = 50,
                      bool showCoordinates = DEFAULT_QGAMEMAP_SHOW_COORDINATES,
                      QWidget* parent = nullptr);

    // - Setters -----------------------------------------------------------------------------
    /**
     * Set the surface of the QGameMap
     */
    void setSurface(Rectangle s);

    /**
     * Set the tiles of the widget
     */
    void setTiles(TileSet tileSet);

    /**
     * Set the size of the tiles
     */
    void setTileSize(unsigned int size);

    /**
     * Show or hide coordinates of the Tiles
     */
    void setCoordinates(bool status);

    /**
     * Toggle Tile coordinates visibility
     */
    void toggleCoordinates();

  private:
    // - Methods -----------------------------------------------------------------------------
    /**
     * Convert a Point to a position (x,y) on the QGameMap
     * @param p Point to figure out position
     * @return Position of the Point on the QWidget
     */
    std::pair<int, int> toPaintCoordinates(Point p);

    /**
     * Paint a Tile on the Map
     * @param p Qt Painter object
     * @param x X component of the Tile to paint
     * @param y Y component of the Tile to paint
     * @param fill Fill color of the Tile
     * @param border Border color of the Tile
     */
    void paintTile(QPainter& p,
                   int x,
                   int y,
                   const QColor& fill = Qt::black,
                   const QColor& border = Qt::black);

    /**
     * Paint the map of the widget
     * @param p Qt Painter object
     */
    void paintMap(QPainter& p);

    /**
     * Qt painting event handler
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

    /**
     * @brief Size of the tiles
     */
    unsigned int tileSize;

    /**
     * @brief If set on true, will show coordinates of the Tiles on the map
     */
    bool showCoordinates;
};

#endif // ILLUVATAR_QGAMEMAP_H
