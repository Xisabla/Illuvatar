/*=========================================================================

Project:   Illuvatar
File:      Vala.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Vala.h"

using namespace std;

Vala::Vala(Map &map, Point point, Direction direction, Faction faction, Master &master): Alliance(map, point, direction, faction, master) {}

void Vala::normalAttack(Minion& other) {
    other.reduceLife(unirand::getValueAround(this->damages, 2));
}

void Vala::hurtItself() {
    this->reduceLife(unirand::getValueAround(this->selfDamages));
}