/*=========================================================================

Project:   Illuvatar
File:      Dragon.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Dragon.h"

using namespace std;

Dragon::Dragon(Map &map, Point point, Direction direction, Faction faction, Master &master): Horde(map, point, direction, faction, master) {}

void Dragon::normalAttack(Minion& other) {
    other.reduceLife(unirand::getValueAround(this->damages, 2));
}

void Dragon::hurtItself() {
    this->reduceLife(unirand::getValueAround(this->selfDamages));
}