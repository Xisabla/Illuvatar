/*=========================================================================

  Project:   Illuvatar
  File:      TileSet.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "map/TileSet.h"

//  --------------------------------------------------------------------------------------
//  TileSet
//  --------------------------------------------------------------------------------------

TileSet::TileSet(std::vector<Tile> set): tiles(std::move(set)) { this->removeDuplicates(); }

TileSet::TileSet(Rectangle surface, Faction faction, bool fill) {
    std::vector<Tile> set;

    if (fill) {
        for (unsigned int x = 0; x < surface.getWidth(); x++) {
            for (unsigned int y = 0; y < surface.getHeight(); y++) {
                set.emplace_back(x, y, faction);
            }
        }
    }

    this->tiles = set;
    this->removeDuplicates();
}

TileSet::TileSet(Rectangle surface, const std::function<Faction(Point)>& predicate, bool fill) {
    std::vector<Tile> set;

    if (fill) {
        for (unsigned int x = 0; x < surface.getWidth(); x++) {
            for (unsigned int y = 0; y < surface.getHeight(); y++) {
                set.emplace_back(x, y, predicate(Point(static_cast<int>(x), static_cast<int>(y))));
            }
        }
    }

    this->tiles = set;
    this->removeDuplicates();
}

//  --------------------------------------------------------------------------------------
//  TileSet > GETTERS
//  --------------------------------------------------------------------------------------

Tile& TileSet::get(const Point& p) {
    auto it = std::find(this->tiles.begin(), this->tiles.end(), Tile(p));

    // Check for existing Tile
    if (it == this->tiles.end() || it - this->tiles.begin() < 0)
        throw std::range_error("Tile (" + std::to_string(p.X()) + ", " + std::to_string(p.Y()) +
                               ") is not member of TileSet");

    return this->tiles[it - this->tiles.begin()];
}

Tile& TileSet::get(int x, int y) { return this->get(Point(x, y)); }

TileSet TileSet::getNeighbours(const Point& p) {
    TileSet neighbours;

    for (int x = p.X() - 1; x <= p.X() + 1; x++) {
        for (int y = p.Y() - 1; y <= p.Y() + 1; y++) {
            // Skip if same point as current one, or if negative components
            if ((x == p.X() && y == p.Y()) || x < 0 || y < 0) continue;

            if (this->exists(x, y)) neighbours.push(this->get(x, y));
        }
    }

    return neighbours;
}

TileSet TileSet::getNeighbours(int x, int y) { return this->getNeighbours(Point(x, y)); }

[[maybe_unused]] Rectangle TileSet::getRect(unsigned int padding_right,
                                            unsigned int padding_bottom) {
    std::vector<int> x(this->size()), y(this->size());

    // Retrieve x and y values of all tiles
    std::transform(this->begin(), this->end(), x.begin(), [](const Tile& t) { return t.X(); });
    std::transform(this->begin(), this->end(), y.begin(), [](const Tile& t) { return t.Y(); });

    //  \---|-------------/---->
    //  0  min           max + pad
    // value = max + padding

    // Retrieve maximums
    unsigned int max_x = static_cast<unsigned int>(*std::max_element(x.begin(), x.end()));
    unsigned int max_y = static_cast<unsigned int>(*std::max_element(y.begin(), y.end()));

    // Compute size
    unsigned int width = max_x + padding_right;
    unsigned int height = max_y + padding_bottom;

    return { width + 1, height + 1 };
}

Rectangle TileSet::getRectAuto() {
    std::vector<int> x(this->size()), y(this->size());

    // Retrieve x and y values of all tiles
    std::transform(this->begin(), this->end(), x.begin(), [](const Tile& t) { return t.X(); });
    std::transform(this->begin(), this->end(), y.begin(), [](const Tile& t) { return t.Y(); });

    //  < d >               < d >
    // \-----|-------------|-----/
    // 0    min           max
    // d = min
    // value = max - min + 2d
    // value = max + min

    // Retrieve maximums & minimums
    unsigned int max_x = static_cast<unsigned int>(*std::max_element(x.begin(), x.end()));
    unsigned int min_x = static_cast<unsigned int>(*std::min_element(x.begin(), x.end()));
    unsigned int max_y = static_cast<unsigned int>(*std::max_element(y.begin(), y.end()));
    unsigned int min_y = static_cast<unsigned int>(*std::min_element(y.begin(), y.end()));

    // Compute size
    unsigned int width = max_x + min_x;
    unsigned int height = max_y + min_y;

    return { width + 1, height + 1 };
}

size_t TileSet::size() { return this->tiles.size(); }

//  --------------------------------------------------------------------------------------
//  TileSet > SETTERS
//  --------------------------------------------------------------------------------------

void TileSet::push(Tile t, bool overwrite) {
    // Check for correct values
    if (t.X() < 0)
        throw std::logic_error(
        "Every Tile in a TileSet should have positive (or zero) components (invalid X value: " +
        std::to_string(t.X()) + ")");
    if (t.Y() < 0)
        throw std::logic_error("Every Tile in a TileSet should have positive (or zero"
                               ") components (invalid Y value: " +
                               std::to_string(t.Y()) + ")");


    // Rewrite existing Tile or append new tile
    if (this->exists(t.X(), t.Y()) && overwrite) this->get(t.X(), t.Y()).setOwner(t.getOwner());
    if (!this->exists(t.X(), t.Y())) this->tiles.push_back(t);
}

void TileSet::emplace(int x, int y, Faction faction, bool overwrite) {
    this->push(Tile(x, y, faction), overwrite);
}

//  --------------------------------------------------------------------------------------
//  TileSet > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void TileSet::merge(TileSet set, bool overwrite) {
    for (auto& t: set) this->push(t, overwrite);
}

[[maybe_unused]] void TileSet::merge(const std::vector<TileSet>& sets, bool overwrite) {
    for (auto& set: sets) this->merge(set, overwrite);
}

[[maybe_unused]] void TileSet::merge(std::vector<Tile> t, bool overwrite) {
    this->merge(TileSet(std::move(t)), overwrite);
}

bool TileSet::exists(const Point& p) {
    return std::find(this->tiles.begin(), this->tiles.end(), Tile(p)) != this->tiles.end();
}

bool TileSet::exists(int x, int y) { return this->exists(Point(x, y)); }

//  --------------------------------------------------------------------------------------
//  TileSet > STATICS
//  --------------------------------------------------------------------------------------

TileSet TileSet::join(const std::vector<TileSet>& sets, bool overwrite) {
    TileSet set;

    for (auto& s: sets) set.merge(s, overwrite);

    return set;
}

//  --------------------------------------------------------------------------------------
//  TileSet > PRIVATE METHODS
//  --------------------------------------------------------------------------------------

void TileSet::removeDuplicates() {
    std::vector<Tile> uniques;

    for (auto& t: this->tiles) {
        if (std::find(uniques.begin(), uniques.end(), t) == uniques.end()) uniques.push_back(t);
    }

    this->tiles = uniques;
}
