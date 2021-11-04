/*=========================================================================

  Project:   Illuvatar
  File:      Map.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MAP_H
#define ILLUVATAR_MAP_H

#include "enums/Faction.h"
#include "enums/Direction.h"
#include "enums/ThingAtPoint.h"
#include "geometry/Rectangle.h"
#include "map/DirectionUtils.h"
#include "map/Tile.h"
#include "map/TileSet.h"
#include "qt/QGameMap.h"

#include <set>
#include <utility>
#include <vector>

class Character;
class Master;

/**
 * @class Map
 * @brief Game map representation
 */
class Map {
  public:
    /**
     * @param tiles Available Tiles on the map
     */
    explicit Map(TileSet tiles);

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
    [[maybe_unused]] Map(unsigned int width, unsigned int height, TileSet tiles = TileSet());

    // - Getters -----------------------------------------------------------------------------
    /**
     * Check if a Tile exists in the Map TileSet
     * @param p Position of the Tile
     * @return True if the Tile exists
     */
    [[nodiscard]] bool exists(const Point& p) const;

    /**
     * Get a Tile on the map
     * @param p Position of the Tile
     * @return The Tile
     */
    Tile& getTile(const Point& p);

    /**
     * Get the neighbours of a Tile on the map
     * @param p Position of the Tile
     * @return A TileSet of neighbours
     */
    [[maybe_unused]] TileSet getNeighbours(const Point& p);

    /**
     * @return The Qt graphical map object linked to the map
     */
    QGameMap* GMap();

    /**
     * @param p Position to check for entity
     * @param allies List of Factions that are considered as allies
     * @return What kind of entity is at the position
     */
    ThingAtPoint getThingAtPoint(const Point& p);

    void jump(Point& from, Point& to, Character* Character);

    Tile& computeLastPosition(const Point& point, const Direction& direction);

    // - Setters -----------------------------------------------------------------------------
    /**
     * Set the faction of a Tile (or add it if it doesn't exist)
     * @param p Position of the Tile
     * @param faction Faction that owns the Tile
     */
    [[maybe_unused]] void setTile(const Point& p, Faction faction = Faction::NoFaction);

    // - Methods -----------------------------------------------------------------------------
    /**
     * Change the Map surface
     * @param surface New surface of the Map
     */
    [[maybe_unused]] void resize(Rectangle surface);

    /**
     * Remove a Tile from the Map
     * @param p Position of the Tile
     */
    [[maybe_unused]] void removeTile(const Point& p);

    /**
     * Synchronize the Qt graphical map and redraw it
     */
    void sync();

    /**
     * @return True if the two points are neighbours on the map
     */
    static bool areNeighbours(const Point& first, const Point& second);

    /**
     * @brief Helper method to sum the components of two Points
     */
    static Point project(const Point& from, const Point& jump);

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
