#include "players/Master.h"

using namespace std;

Master::Master(Map &map, Point point, Faction faction): Character(map, point, faction) {}

string Master::GetMessage(Minion& minion) {
    return "";
}

void Master::GiveMessage(Minion& minion) { }
