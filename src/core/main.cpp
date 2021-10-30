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

#include <QApplication>

using namespace std;
using namespace pathfinder;
using namespace directionutils;

// TODO: Use (x, y, ...) or (Point, ...) params everywhere but not both (choose one -> Point ?)
// TODO (late): Remove all unused methods

int main(int argc, char* argv[]) {
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


    Path refPath = { map.getTile(Point(9,6)),
                      map.getTile(Point(9,7)),
                      map.getTile(Point(10,7)),
                      map.getTile(Point(11,7)),
                      map.getTile(Point(11,6)) };
    DirectionalPath path = {};
    path = pathfinder::straightenerAndCutter(map, refPath, path, Direction::N, 100);
    for (pair<Tile, Direction> step : path) cout << step.first << " - " << step.second << endl;

    cout << endl;

    map.getTile(Point(9,6)).setObstacle();
    map.getTile(Point(9,7)).setObstacle();
    map.getTile(Point(10,7)).setObstacle();
    // map.getTile(Point(11,7)).setObstacle();
    // map.getTile(Point(11,6)).setObstacle();

    path = computeShortestPath(map, map.getTile(Point(10,5)), map.getTile(Point(6, 4)), Direction::N, 100);
    for (pair<Tile, Direction> step : path) cout << step.first << " - " << step.second << endl;
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
