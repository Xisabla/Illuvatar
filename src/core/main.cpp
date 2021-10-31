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


    // Path refPath = { map.getTile(Point(9,6)),
    //                   map.getTile(Point(9,7)),
    //                   map.getTile(Point(10,7)),
    //                   map.getTile(Point(11,7)),
    //                   map.getTile(Point(11,6)) };
    DirectionalPath path = {};
    // path = pathfinder::straightenerAndCutter(map, refPath, path, Direction::N, 100);
    // for (pair<Tile, Direction> step : path) cout << step.first << " - " << step.second << endl;

    // cout << endl;

    map.getTile(Point(9,6)).setObstacle();
    map.getTile(Point(9,7)).setObstacle();
    map.getTile(Point(10,7)).setObstacle();
    map.getTile(Point(11,7)).setObstacle();
    // map.getTile(Point(11,6)).setObstacle();

    // path = computeShortestPath(map, map.getTile(Point(10,5)), map.getTile(Point(6, 4)), Direction::N, 100);
    // for (pair<Tile, Direction> step : path) cout << step.first << " - " << step.second << endl;
    
    // cout << endl;

    Master master = Master(map, Point(14,14), Faction::Valars);
    // Minion minion = Minion(map, map.getTile(Point(10, 8)), Faction::Valars, master);
    
    // path = minion.findMaster(10);
    // for (pair<Tile, Direction> step : path) cout << step.first << " - " << step.second << endl;

    // Direction dir = Direction::N;
    // pair<ThingAtPoint, Point> check = minion.checkDirection(minion.getTile(), dir);
    // cout << endl << check.first << " on point " << check.second << endl << endl;

    // dir = Direction::NW;
    // check = minion.checkDirection(minion.getTile(), dir);
    // cout << endl << check.first << " on point " << check.second << endl << endl;

    // dir = Direction::NE;
    // check = minion.checkDirection(minion.getTile(), dir);
    // cout << endl << check.first << " on point " << check.second << endl << endl;

    // dir = Direction::N;
    // check = minion.checkDirection(map.getTile(Point(10,5)), dir);
    // cout << check.first << " on point " << check.second << endl << endl;

    // map.getTile(Point(9,9)).setOwner(Faction::Eldars);
    // map.getTile(Point(10,9)).setOwner(Faction::Valars);
    // map.getTile(Point(11,9)).setOwner(Faction::Dragons);
    // cout << "nb minion autour : " << minion.checkAround().size() << endl;
    // for (pair<ThingAtPoint, Point> check2 : minion.checkAround()) cout << check2.first << " on point " << check2.second << endl;

    // cout << endl << minion.interactsWithSurroundings() << endl << endl;

    // path = minion.explorate(10);
    // cout << "path size : " << path.size() << endl;
    // for (pair<Tile, Direction> step : path) cout << "\t" << step.first << " - " << step.second << endl;

    // cout << endl;

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
