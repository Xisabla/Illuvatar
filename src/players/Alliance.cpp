/*=========================================================================

Project:   Illuvatar
File:      Alliance.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Alliance.h"

using namespace std;

Alliance::Alliance(Map &map, Point point, Faction faction, Master &master): Minion(map, point, faction, master) {}

void Alliance::specialAttack(Minion& other) {
    other.reduceEnergy(unirand::getValueAround(this->energyReduction, 2));
    this->normalAttack(other);
}
