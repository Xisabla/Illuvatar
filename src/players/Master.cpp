#include "players/Master.h"

using namespace std;

Master::Master(Map &map, Tile &tile, Faction faction): Character(map, tile, faction) {}

string Master::GetMessage(Minion& minion) {
    return "";
}

void Master::GiveMessage(Minion& minion) { }
