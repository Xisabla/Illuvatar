/*=========================================================================

  Project:   Illuvatar
  File:      Map.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MAP_H
#define ILLUVATAR_MAP_H

#include "geometry/Rectangle.h"
#include "map/Tile.h"
#include "map/TileSet.h"
#include "qt/QGameMap.h"

#include <utility>
#include <vector>

/**
 * @class Map
 * @brief Game map representation
 */
class Map {
  public:
    /**
     * @param tiles Available Tiles on the map
     */
    explicit Map(TileSet  tiles);

    /**
     * @param surface Map rectangular shape
     * @param tiles Available Tiles on the map
     */
    explicit Map(Rectangle surface, TileSet tiles = TileSet());

    /**
     * @param width Map width
     * @param height Map height
     * @param tiles Available Tiles on the map
     */
    Map(unsigned int width, unsigned int height, TileSet tiles = TileSet());

    // - Getters -----------------------------------------------------------------------------
    /**
     * @return The Qt graphical map object linked to the map
     */
    QGameMap* GMap();

    // - Setters -----------------------------------------------------------------------------
    // TODO: set/add/remove Tile(s)
    // TODO: setTileOwnership
    // TODO: getTile (remove if unused)
    // TODO: resize

    // - Methods -----------------------------------------------------------------------------
    /**
     * Synchronize the Qt graphical map and redraw it
     */
    void sync();

  private:
    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Qt graphical map linked to the map
     */
    QGameMap* gmap;

    /**
     * @brief Available Tiles on the map
     */
    TileSet tiles;
};

#endif // ILLUVATAR_MAP_H
