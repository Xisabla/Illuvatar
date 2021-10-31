/*=========================================================================

  Project:   Illuvatar
  File:      Tile.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_TILE_H
#define ILLUVATAR_TILE_H

#include "geometry/Point.h"
#include "wip.h"

#include <iostream>
#include <utility>

/**
 * @enum Faction
 * @brief Available Factions in the simulation
 */
enum Faction { Eldars, Valars, Dragons, Werewolves, NoFaction };

std::ostream& operator<<(std::ostream& out, Faction value);

/**
 * @class Tile
 * @brief Representation of a tile on the map. Stores ownership and characters
 */
class Tile : public Point {
  public:
    /**
     * @param x X position of the Tile
     * @param y Y position of the Tile
     * @param faction Faction that owns the Tile
     */
    Tile(int x, int y, Faction faction = NoFaction);

    /**
     * @param p Position of the Tile
     * @param faction Faction that owns the Tile
     */
    explicit Tile(Point p, Faction faction = NoFaction);

    // - Getters -----------------------------------------------------------------------------
    /**
     * @return The faction owning the Tile
     */
    Faction getOwner();

    /**
     * @param f Faction to test
     * @return True of the faction is owning the Tile
     */
    bool belongsTo(Faction f);

    /**
     * @return True if the Tile is an obstacle
     */
    bool isObstacle() const;

    // - Setters -----------------------------------------------------------------------------
    /**
     * Sets the faction owning the Tile
     * @param f Faction to set ownership to
     */
    void setOwner(Faction f);

    /**
     * @brief Set the Tile as an obstacle
     */
    void setObstacle();

    /**
     * @brief Unset the Tile as an obstacle
     */
    void unsetObstacle();

    /**
     * Remove current faction ownership (set to NoFaction)
     */
    void removeOwnership();

    // - Operators ---------------------------------------------------------------------------
    inline bool operator==(const Tile& t) const { return Point::operator==(t); }

    inline bool operator<(const Tile& t) const { return Point::operator<(t); }

    inline friend std::ostream& operator<<(std::ostream& out, Tile& t) {
        return out << t.getPoint() << " " << t.getOwner();
    }

  private:
    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Faction that owns the Tile, can be set to NoFaction for unowned Tile
     */
    Faction owner;

    /**
     * @brief Is the Tile an obstacle ?
     */
    bool obstacle = false;

    // TODO: Character
};

#endif // ILLUVATAR_TILE_H
