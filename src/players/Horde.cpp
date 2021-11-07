/*=========================================================================

Project:   Illuvatar
File:      Horde.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Horde.h"

using namespace std;

Horde::Horde(Map &map, Point point, Direction direction, Faction faction, Master &master): Minion(map, point, direction, faction, master) {}

void Horde::specialAttack(Minion& other) {
    this->normalAttack(other);
    this->restoreLife(unirand::getValueAround(this->lifeHeal, 2));
}
