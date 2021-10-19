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

void SafeZone::setPoints(std::vector<Point> points) { this->points = points; }

void SafeZone::addPoint(Point p) {
    if (std::find(this->points.begin(), this->points.end(), p) == this->points.end())
        this->points.push_back(p);
}

void SafeZone::removePoint(Point p) {
    std::remove_if(this->points.begin(), this->points.end(), [p](Point pt) { return p == pt; });
}

void SafeZone::addPoints(std::vector<Point> points) {
    for (auto& p: points) addPoint(p);
}

void SafeZone::removePoints(std::vector<Point> points) {
    for (auto& p: points) removePoint(p);
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

    this->gmap = new QGameMap(width, height);
}

//  --------------------------------------------------------------------------------------
//  Map > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Map::syncGMap() { this->setGMapSafezones(); }

QGameMap* Map::GMap() {
    this->syncGMap();

    return this->gmap;
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

void Map::setGMapSafezones() {
    ColoredPoints points;

    for (auto& p: this->sz_dragons.getPoints()) points.emplace_back(p, Qt::red);
    for (auto& p: this->sz_eldars.getPoints()) points.emplace_back(p, Qt::green);
    for (auto& p: this->sz_valars.getPoints()) points.emplace_back(p, Qt::lightGray);
    for (auto& p: this->sz_werewolves.getPoints()) points.emplace_back(p, Qt::darkRed);

    this->gmap->setPoints(points);
}
