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
 * @enum Preset
 * @brief Map preset generators, used a templates to generate the map
 */
enum Preset { Turtle, Square, Random, Default = Turtle };

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

    // - Setters -----------------------------------------------------------------------------
    void setPreset(Preset preset);

    static void setDefaultPreset(Preset preset);

    // - Methods -----------------------------------------------------------------------------
    void generate();
    void sync();

    void linkCharacter(unsigned int x, unsigned int y, Character* character);
    void unlinkCharacter(Character* character);
    bool containsCharacter(unsigned int x, unsigned int y);
    
    bool exists(const superTypes::Point& p) const;
    ThingAtPoint getThingAtPoint(const superTypes::Point& p);
    superTypes::Point computeLastPosition(const superTypes::Point& point, const Direction& direction);
    static superTypes::Point project(const superTypes::Point& from, const superTypes::Point& jump);
    static bool areNeighbours(const superTypes::Point& first, const superTypes::Point& second);
    void jump(superTypes::Point from, superTypes::Point to, Character* character);

    // - Friends -----------------------------------------------------------------------------

  private:
    // - Methods -----------------------------------------------------------------------------
    static void generateDisk(
    double radius, unsigned int centerX, unsigned int centerY, Faction owner = Faction::NoFaction);
    static void generateSquare(unsigned int topX,
                               unsigned int topY,
                               unsigned int bottomX,
                               unsigned int bottomY,
                               Faction owner = Faction::NoFaction);

    // - Attributes --------------------------------------------------------------------------
    Domain _domain;
    Preset _preset;
    QGameMap* _qgmap;

    std::map<std::pair<unsigned int, unsigned int>, Character*> _characters;

    static Preset defaultPreset;
};


#endif // ILLUVATAR_MAP_H
