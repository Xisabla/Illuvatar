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
    TileSet tiles = TileSet::join({ generators::disk(5, Point(10, 10)),
                                    generators::disk(2.8, Point(6, 6), Werewolves),
                                    generators::disk(2.8, Point(14, 14), Valars),
                                    generators::disk(2.8, Point(6, 14), Eldars),
                                    generators::disk(2.8, Point(14, 6), Dragons) },
                                  true);

    tiles.push(Tile(10, 10, Werewolves));

    // Instantiate map
    Map map(tiles);

    // Create and show window
    MainWindow window(map);
    window.show();

    // Synchronize map tiles
    map.sync();

    return QApplication::exec();
}
