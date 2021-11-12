/*=========================================================================

  Project:   Illuvatar
  File:      Tile.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_TILE_H
#define ILLUVATAR_TILE_H

#include "enums/Faction.h"

#include <iostream>
#include <vector>

/**
 * @class Tile
 * @brief Representation of a Tile on the map. Stores all instances, does not allow multiple
 *  instances with the same attributes x and y.
 */
class Tile {
  public:
    Tile(unsigned int x, unsigned int y, Faction owner = Faction::NoFaction);
    ~Tile();

    // - Getters -----------------------------------------------------------------------------
    [[nodiscard]] unsigned int id() const;
    [[nodiscard]] unsigned int x() const;
    [[nodiscard]] unsigned int y() const;
    [[nodiscard]] Faction getOwner() const;
    // TODO: Character* getCharacter()

    // NOTE: Should have another name than "rectangle", like
    //  - Area, Box, Domain, Zone
    // TODO: move following ones to map:
    //  - Rectangle getRect(padding_right, padding_bottom) const;
    //  - Rectangle getRectAuto() const;

    static unsigned int count();
    static Tile* get(unsigned int x, unsigned int y);
    static std::vector<Tile*> getAll();
    static std::vector<Tile*> getNeighbours(unsigned int x, unsigned int y);

    // - Setters -----------------------------------------------------------------------------
    void setOwnership(Faction owner);
    void removeOwnership();

    // - Methods -----------------------------------------------------------------------------
    [[nodiscard]] bool isOwnedBy(Faction f) const;
    // TODO: bool containsObstacle() const;
    // TODO: bool containsCharacter() const;

    static bool exists(unsigned int x, unsigned int y);
    static void remove(unsigned int x, unsigned int y);
    static void removeAll();

    static Tile*
    safeCreate(unsigned int x, unsigned int y, Faction owner = Faction::NoFaction, bool overwrite = true);

    // - Operators ---------------------------------------------------------------------------
    inline bool operator==(const Tile& t) const { return _id == t.id(); }
    inline bool operator<(const Tile& t) const { return _id < t.id(); }

  private:
    // - Attributes --------------------------------------------------------------------------
    unsigned int _id;
    /**
     * @brief X component of the Tile
     */
    const unsigned int _x;
    /**
     * @brief Y component of the Tile
     */
    const unsigned int _y;
    /**
     * @brief Faction that owns the Tile, set to "NoFaction" if not a SafeZone
     */
    Faction _owner;

    /**
     * @brief ID counter
     */
    static unsigned int _i;
    /**
     * @brief All instances of the Class
     */
    static std::vector<Tile*> _instances;
};

#endif // ILLUVATAR_TILE_H
