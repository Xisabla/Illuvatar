/*=========================================================================

  Project:   Illuvatar
  File:      Map.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MAP_H
#define ILLUVATAR_MAP_H

#include "map/Point.h"
#include "map/QGameMap.h"

#include <QColor>
#include <QMainWindow>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

// <--- Temporary stuff that will get included later
enum Alliance { Evil, Good };
enum Faction { Eldars, Valars, Dragons, Werewolves };
// Temporary stuff that will get included later --->

/**
 * @class SafeZone
 * @brief Non-fighting area where the master of a faction is located
 */
class SafeZone {
  public:
    SafeZone(Faction faction, std::vector<Point> points = {});

    // - Getters -----------------------------------------------------------------------------
    std::vector<Point> getPoints();

    // - Setters -----------------------------------------------------------------------------
    void setTiles(std::vector<Point> points);
    void addTile(Point p);
    void removeTile(Point p);
    void addTiles(std::vector<Point> points);
    void removeTiles(std::vector<Point> points);

  private:
    // - Attributes --------------------------------------------------------------------------
    Faction faction;
    std::vector<Point> points;
};

/**
 * @enum Corner
 * @brief Corners of the map
 */
enum Corner { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

/**
 * @class Map
 * @brief Game map
 */
class Map {
  public:
    Map(int width, int height);

    // - Methods -----------------------------------------------------------------------------
    QGameMap toQGameMap();

  private:
    // - Methods -----------------------------------------------------------------------------
    SafeZone autoSafezone(Faction faction, Corner corner);

    // - Attributes --------------------------------------------------------------------------
    int width, height;
    SafeZone sz_eldars;
    SafeZone sz_valars;
    SafeZone sz_dragons;
    SafeZone sz_werewolves;
};

#endif // ILLUVATAR_MAP_H
