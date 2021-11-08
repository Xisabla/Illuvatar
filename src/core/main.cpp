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
#include "players/Dragon.h"
#include "players/Eldar.h"
#include "players/Vala.h"
#include "players/Werewolf.h"
#include "superTypes.h"
#include "unirand.h"

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
    // Fix size for smaller screens (can remove/change if needed)
    map.GMap()->setTileSize(40);

    // Add masters
    Master master_d(map, Point(14, 6), Faction::Dragons, { "Da", "Db", "Dc", "Dd", "De" });
    Master master_e(map, Point(6, 14), Faction::Eldars, { "Ea", "Eb", "Ec", "Ed", "Ee" });
    Master master_v(map, Point(14, 14), Faction::Valars, { "Va", "Vb", "Vc", "Vd", "Ve" });
    Master master_w(map, Point(6, 6), Faction::Werewolves, { "Wa", "Wb", "Wc", "Wd", "We" });
    
    // map.getTile(master_d.getPoint()).setCharacter(dynamic_cast<Character*>(&master_d));
    // map.getTile(master_e.getPoint()).setCharacter(dynamic_cast<Character*>(&master_e));
    // map.getTile(master_v.getPoint()).setCharacter(dynamic_cast<Character*>(&master_v));
    // map.getTile(master_w.getPoint()).setCharacter(dynamic_cast<Character*>(&master_w));

    // Add random minions on the map, just testing
    std::vector<Minion*> minions;

    for (auto& t: tiles) {
        if (t.isOccupied()) continue;

        switch(rand() % 8) {
            case 0:
                minions.emplace_back(new Dragon(map, t.getPoint(), master_d));
                break;
            case 1:
                minions.emplace_back(new Eldar(map, t.getPoint(), master_e));
                break;
            case 2:
                minions.emplace_back(new Vala(map, t.getPoint(), master_v));
                break;
            case 3:
                minions.emplace_back(new Werewolf(map, t.getPoint(), master_w));
                break;
        }
    }

    // minions[0].move();

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
