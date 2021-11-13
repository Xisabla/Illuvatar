/*=========================================================================

  Project:   Illuvatar
  File:      Map.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MAP_H
#define ILLUVATAR_MAP_H

#include "characters/Character.h"
#include "gui/QGameMap.h"
#include "map/Domain.h"
#include "map/Tile.h"
#include "templates/Singleton.h"
#include "enums/Faction.h"
#include "enums/Direction.h"
#include "enums/DirectionUtils.h"
#include "enums/ThingAtPoint.h"

#include "superTypes.h"

/**
 * @class Map
 * @brief Short description of the class
 */
SINGLETON(Map) {
  public:
    explicit Map(_token t);

    // - Getters -----------------------------------------------------------------------------
    [[nodiscard]] unsigned int width() const;
    [[nodiscard]] unsigned int height() const;
    [[nodiscard]] QGameMap* qgmap() const;

    Character* getCharacter(unsigned int x, unsigned int y);
    Character* getMaster(Faction faction);
    std::map<std::pair<unsigned int, unsigned int>, Character*>& characters();

    // - Methods -----------------------------------------------------------------------------
    void generate();
    void sync();

    void linkCharacter(unsigned int x, unsigned int y, Character* character);
    void unlinkCharacter(Character* character);
    bool containsCharacter(unsigned int x, unsigned int y);
    void removeAllCharacters();
    
    bool exists(const superTypes::Point& p) const;
    ThingAtPoint getThingAtPoint(const superTypes::Point& p);
    superTypes::Point computeLastPosition(const superTypes::Point& point, const Direction& direction);
    static superTypes::Point project(const superTypes::Point& from, const superTypes::Point& jump);
    static bool areNeighbours(const superTypes::Point& first, const superTypes::Point& second);
    void jump(superTypes::Point newPos, Character* character);

    // - Friends -----------------------------------------------------------------------------

  private:
    // - Methods -----------------------------------------------------------------------------
    static void generateDisk(double radius, unsigned int centerX, unsigned int centerY, Faction owner = Faction::NoFaction);

    // - Attributes --------------------------------------------------------------------------
    Domain _domain;
    QGameMap* _qgmap;

    std::map<std::pair<unsigned int, unsigned int>, Character*> _characters;
};


#endif // ILLUVATAR_MAP_H
