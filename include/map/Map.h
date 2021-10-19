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
    /**
     * @param faction Faction that owns the safezone
     * @param points All points that belong to the safezone
     */
    SafeZone(Faction faction, std::vector<Point> points = {});

    // - Getters -----------------------------------------------------------------------------
    /**
     * @return All the points of the safezone
     */
    std::vector<Point> getPoints();

    // - Setters -----------------------------------------------------------------------------
    /**
     * Overwrite and set all the points of the safezone
     * @param points All points of the safezone
     */
    void setPoints(std::vector<Point> points);

    /**
     * Add a point to the safezone area
     * @param p Point to add
     */
    void addPoint(Point p);

    /**
     * Remove a point from the safezone area
     * @param p Point to remove
     */
    void removePoint(Point p);

    /**
     * Add multiple points in the safezone area
     * @param points Points to add
     */
    void addPoints(std::vector<Point> points);

    /**
     * Remove multiple points from the safezone area
     * @param points Points to remove
     */
    void removePoints(std::vector<Point> points);

  private:
    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Faction that owns the safezone
     */
    Faction faction;

    /**
     * @brief All points that belong to the safezone
     */
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
    /**
     * @param width Width of the map (number of tiles)
     * @param height Height of the map (number of tiles)
     */
    Map(int width, int height);

    // - Methods -----------------------------------------------------------------------------
    /**
     * Synchronize the graphical map with the map object
     */
    void syncGMap();

    // - Getters -----------------------------------------------------------------------------
    /**
     * @return The linked graphical map reference
     */
    QGameMap* GMap();

  private:
    // - Methods -----------------------------------------------------------------------------
    /**
     * Auto generate safezone (rectangle shaped, size depending on map size)
     * @param faction Faction to generate the safezone for
     * @param corner Location of the safezone
     * @return The generated safezone
     */
    SafeZone autoSafezone(Faction faction, Corner corner);

    /**
     * Set the safezones on the graphical map object
     */
    void setGMapSafezones();

    // - Attributes --------------------------------------------------------------------------
    /**
     * @brief Width of the map (number of tiles)
     */
    int width;

    /**
     * @brief Height of the map (number of tiles)
     */
    int height;

    /**
     * @brief Safezone that belongs to dragons
     */
    SafeZone sz_dragons;

    /**
     * @brief Safezone that belongs to eldars
     */
    SafeZone sz_eldars;

    /**
     * @brief Safezone that belongs to valars
     */
    SafeZone sz_valars;

    /**
     * @brief Safezone that belongs to werewolves
     */
    SafeZone sz_werewolves;

    /**
     * @brief Reference to graphical game map object (QGameMap)
     */
    QGameMap* gmap;
};

#endif // ILLUVATAR_MAP_H
