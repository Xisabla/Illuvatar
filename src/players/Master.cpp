#include "players/Master.h"

using namespace std;

Master::Master(Map &map, Point point, Faction faction): Character(map, point, faction) {}

string Master::getMessage(Minion& minion) {
    return "";
}

void Master::giveMessage(Minion& minion) { }
