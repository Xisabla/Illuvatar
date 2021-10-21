/*=========================================================================

Project:   Illuvatar
File:      MainWindow.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/MainWindow.h"
#include "map/Generators.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Maps tiles (demo)
    std::vector<Tile> tiles;

    auto c_tiles = generators::disk(5, Point(10, 10));
    auto w_tiles = generators::disk(2.8, Point(6, 6), Werewolves);
    auto v_tiles = generators::disk(2.8, Point(14, 14), Valars);
    auto e_tiles = generators::disk(2.8, Point(6, 14), Eldars);
    auto d_tiles = generators::disk(2.8, Point(14, 6), Dragons);

    tiles.reserve(w_tiles.size() + v_tiles.size() + e_tiles.size() + d_tiles.size() + c_tiles.size());
    for (auto& t: w_tiles) tiles.push_back(t);
    for (auto& t: v_tiles) tiles.push_back(t);
    for (auto& t: e_tiles) tiles.push_back(t);
    for (auto& t: d_tiles) tiles.push_back(t);
    for (auto& t: c_tiles) tiles.push_back(t);

    // Instantiate map
    Map map(20, 20, tiles);

    // Create and show window
    MainWindow window(map);
    window.show();

    // Synchronize map tiles
    map.sync();

    return QApplication::exec();
}
