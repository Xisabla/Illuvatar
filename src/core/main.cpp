/*=========================================================================

Project:   Illuvatar
File:      MainWindow.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/MainWindow.h"
#include "map/Generators.h"
#include "map/PathFinder.h"
#include "map/DirectionUtils.h"
#include "players/Minion.h"
#include "players/Master.h"

#include <QApplication>

using namespace std;
using namespace pathfinder;
using namespace directionutils;

// TODO: Use (x, y, ...) or (Point, ...) params everywhere but not both (choose one -> Point ?)
// TODO (late): Remove all unused methods

int main(int argc, char* argv[]) {
    srand(time(NULL));

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


    map.getTile(Point(9,6)).setObstacle();
    map.getTile(Point(9,7)).setObstacle();
    map.getTile(Point(10,7)).setObstacle();
    map.getTile(Point(11,7)).setObstacle();

    Master master = Master(map, Point(14,14), Faction::Valars);
    Minion minion = Minion(map, Point(10, 8), Direction::N, Faction::Valars, master);

    map.getTile(Point(9,9)).setOwner(Faction::Eldars);
    map.getTile(Point(10,9)).setOwner(Faction::Valars);
    map.getTile(Point(11,9)).setOwner(Faction::Dragons);

    Minion(map, Point(10, 10), Direction::S, Faction::Valars, master).move();

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
