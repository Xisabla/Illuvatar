/*=========================================================================

  Project:   Illuvatar
  File:      Map.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/Map.h"

//  --------------------------------------------------------------------------------------
//  SafeZone
//  --------------------------------------------------------------------------------------

SafeZone::SafeZone(Faction faction, std::vector<Point> points): faction(faction), points(points) { }

//  --------------------------------------------------------------------------------------
//  SafeZone > GETTERS
//  --------------------------------------------------------------------------------------

std::vector<Point> SafeZone::getPoints() { return this->points; }

//  --------------------------------------------------------------------------------------
//  SafeZone > SETTERS
//  --------------------------------------------------------------------------------------

void SafeZone::setTiles(std::vector<Point> points) { this->points = points; }

void SafeZone::addTile(Point p) {
    if (std::find(this->points.begin(), this->points.end(), p) == this->points.end())
        this->points.push_back(p);
}

void SafeZone::removeTile(Point p) {
    std::remove_if(this->points.begin(), this->points.end(), [p](Point pt) { return p == pt; });
}

void SafeZone::addTiles(std::vector<Point> points) {
    for (auto& p: points) addTile(p);
}

void SafeZone::removeTiles(std::vector<Point> points) {
    for (auto& p: points) removeTile(p);
}

//  --------------------------------------------------------------------------------------
//  Map
//  --------------------------------------------------------------------------------------

Map::Map(int width, int height)
: width(width), height(height), sz_dragons(SafeZone(Dragons)), sz_werewolves(SafeZone(Werewolves)),
  sz_valars(SafeZone(Valars)), sz_eldars(SafeZone(Eldars)) {
    this->sz_dragons = autoSafezone(Dragons, TOP_RIGHT);
    this->sz_werewolves = autoSafezone(Werewolves, TOP_LEFT);
    this->sz_valars = autoSafezone(Valars, BOTTOM_LEFT);
    this->sz_eldars = autoSafezone(Eldars, BOTTOM_RIGHT);
}

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

QGameMap Map::toQGameMap() {
    ColoredPoints coloredPoints;

    for (auto& p: this->sz_dragons.getPoints()) coloredPoints.emplace_back(p, Qt::red);
    for (auto& p: this->sz_eldars.getPoints()) coloredPoints.emplace_back(p, Qt::green);
    for (auto& p: this->sz_valars.getPoints()) coloredPoints.emplace_back(p, Qt::lightGray);
    for (auto& p: this->sz_werewolves.getPoints()) coloredPoints.emplace_back(p, Qt::darkRed);

    return QGameMap(this->width, this->height, coloredPoints);
}

//  --------------------------------------------------------------------------------------
//  Map > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

SafeZone Map::autoSafezone(Faction faction, Corner corner) {
    int width = static_cast<int>(ceil(log(static_cast<float>(this->width))));
    int height = static_cast<int>(ceil(log(static_cast<float>(this->height))));

    std::vector<Point> points;
    int x, y;

    for (int dx = 0; dx < width; dx++) {
        if (corner == TOP_LEFT || corner == BOTTOM_LEFT) x = 0 + dx;
        if (corner == TOP_RIGHT || corner == BOTTOM_RIGHT) x = this->width - dx - 1;

        for (int dy = 0; dy < height; dy++) {
            if (corner == TOP_LEFT || corner == TOP_RIGHT) y = 0 + dy;
            if (corner == BOTTOM_LEFT || corner == BOTTOM_RIGHT) y = this->height - dy - 1;

            points.emplace_back(x, y);
        }
    }

    return SafeZone(faction, points);
}
