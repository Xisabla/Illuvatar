/*=========================================================================

  Project:   Illuvatar
  File:      TileSet.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_TILESET_H
#define ILLUVATAR_TILESET_H

#include "geometry/Rectangle.h"
#include "map/Tile.h"

#include <functional>
#include <stdexcept>
#include <vector>

/**
 * @class TileSet
 * @brief Tiles aggregator. Allow only one Tile for a given position (x,y)
 */
class TileSet {
  public:
    /**
     * @param set TileSet to import as vector of Tile
     */
    explicit TileSet(std::vector<Tile> set = {});

    /**
     * @param surface Surface of the map
     * @param faction Faction that owns the generated Tiles
     * @param fill If set on true, will fill all the surface with Tiles
     */
    explicit TileSet(Rectangle surface, Faction faction = NoFaction, bool fill = true);

    /**
     * @param surface Surface of the map
     * @param predicate Predicate to determinate the faction that owns the generated Tiles
     * @param fill If set on true, will fill all the surface with Tiles
     */
    TileSet(Rectangle surface, const std::function<Faction(Point p)>& predicate, bool fill = true);

    // - Getters -----------------------------------------------------------------------------
    /**
     * @param p Point to find
     * @return The Tile at the same coordinates of the point
     */
    Tile& get(const Point& p);

    /**
     * @param x X component of the point to find
     * @param y Y component of the point to find
     * @return The Tile at the given coordinates
     */
    Tile& get(int x, int y);

    /**
     * @param p Point to find neighbours from
     * @return A TileSet with all the found neighbours
     */
    TileSet getNeighbours(const Point& p);

    /**
     * @param x X component of the Tile to find neighbours from
     * @param y Y component of the Tile to find neighbours from
     * @return A TileSet with all the found neighbours
     */
    TileSet getNeighbours(int x, int y);

    /**
     * @param padding_right Padding at the right of the computed surface
     * @param padding_bottom Padding at the bottom of the computed surface
     * @return The smallest computed surface that contains all the Tiles (+ paddings)
     */
    [[maybe_unused]] Rectangle getRect(unsigned int padding_right = 0,
                                       unsigned int padding_bottom = 0);

    /**
     * @return A computed surface that contains all the Tiles and tries to center them by adding
     * automatic padding
     */
    Rectangle getRectAuto();

    /**
     * @return The number of Tiles in the set
     */
    size_t size();

    // - Setters -----------------------------------------------------------------------------
    /**
     * @param t Tile to add
     * @param overwrite If set on true, will overwrite the (maybe) existing Tile
     */
    void push(Tile t, bool overwrite = true);

    /**
     * @param x X component of the Tile
     * @param y Y component of the Tile
     * @param faction Faction that owns the Tile
     * @param overwrite If set on true, will overwrite the (maybe) existing Tile
     */
    void emplace(int x, int y, Faction faction = NoFaction, bool overwrite = true);

    // - Methods -----------------------------------------------------------------------------
    /**
     * Remove a Tile from the TileSet
     * @param p Position of the Tile
     */
    void remove(const Point& p);

    /**
     * Remove a Tile from the TileSet
     * @param x X component of the Tile
     * @param y Y component of the Tile
     */
    void remove(int x, int y);

    /**
     * @param p Point to find
     * @return True if a Tile exists at the Point coordinates
     */
    bool exists(const Point& p);

    /**
     * @param x X component of the Tile
     * @param y Y component of the Tile
     * @return True if a Tile exists at the given coordinates
     */
    bool exists(int x, int y);

    /**
     * Merge the current TileSet with another one
     * @param set TileSet to merge with
     * @param overwrite If set on True, the new Tiles will overwrite the (maybe) existing ones
     */
    void merge(TileSet set, bool overwrite = true);

    /**
     * Merge the current TileSet with a list of TileSets
     * @param sets TileSets to merge with
     * @param overwrite If set on True, the new Tiles will overwrite the (maybe) existing ones
     */
    [[maybe_unused]] void merge(const std::vector<TileSet>& sets, bool overwrite = true);

    /**
     * Merge the current TileSet with a list of Tiles
     * @param t Tiles to merge with
     * @param overwrite If set on True, the new Tiles will overwrite the (maybe) existing ones
     */
    [[maybe_unused]] void merge(std::vector<Tile> t, bool overwrite = true);

    // - Iterators ---------------------------------------------------------------------------
    auto begin() { return this->tiles.begin(); }
    auto end() { return this->tiles.end(); }

    // - Statics -----------------------------------------------------------------------------
    /**
     * @brief Generate a TileSet that merges all the given ones
     * @param sets TileSets to merge
     * @param overwrite If set on True, the new Tiles will overwrite the (maybe) existing ones
     * @return A TileSets that contains all the Tiles of the given TileSets
     */
    static TileSet join(const std::vector<TileSet>& sets, bool overwrite = true);

  private:
    // - Methods -----------------------------------------------------------------------------
    /**
     * @brief Remove Tiles with same coordinates (first to be found are kept)
     */
    void removeDuplicates();

    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Tiles of the set
     */
    std::vector<Tile> tiles;
};

#endif // ILLUVATAR_TILESET_H
