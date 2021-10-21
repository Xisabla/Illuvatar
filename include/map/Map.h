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
#include "qt/QGameMap.h"

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
    explicit Map(const std::vector<Tile>& tiles);

    /**
     * @param surface Map rectangular shape
     * @param tiles Available Tiles on the map
     */
    explicit Map(Rectangle surface, std::vector<Tile> tiles = {});

    /**
     * @param width Map width
     * @param height Map height
     * @param tiles Available Tiles on the map
     */
    Map(unsigned int width, unsigned int height, std::vector<Tile> tiles = {});

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
    std::vector<Tile> tiles;
};

#endif // ILLUVATAR_MAP_H
