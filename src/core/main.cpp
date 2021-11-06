/*=========================================================================

Project:   Illuvatar
File:      MainWindow.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/MainWindow.h"
#include "map/Generators.h"
#include "map/PathFinder.h"
#include "players/Minion.h"
#include "superTypes.h"

#include <QApplication>

using namespace std;
using namespace pathfinder;
using namespace directionutils;
using namespace superTypes;

// TODO: Use (x, y, ...) or (Point, ...) params everywhere but not both (choose one -> Point ?)
// TODO (late): Remove all unused methods

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    QApplication app(argc, argv);

    // Maps tiles (demo)
    TileSet tiles = TileSet::join({ generators::disk(5, Point(10, 10)),
                                    generators::disk(2.8, Point(6, 6), Faction::Werewolves),
                                    generators::disk(2.8, Point(14, 14), Faction::Valars),
                                    generators::disk(2.8, Point(6, 14), Faction::Eldars),
                                    generators::disk(2.8, Point(14, 6), Faction::Dragons) },
                                  true);

    // Instantiate map
    Map map(tiles);

    // add loop to test moves
    // pathfinding(position maitre) => rendre message ou plus d'énergie
    // explo(directionPrincipale) => se déplacer sur la map selon une direction principale

    // Create and show window
    MainWindow window(map);
    window.show();

    // Synchronize map tiles
    map.sync();

    return QApplication::exec();
}
