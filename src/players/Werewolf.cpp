/*=========================================================================

Project:   Illuvatar
File:      Werewolf.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Werewolf.h"

using namespace std;

Werewolf::Werewolf(Map &map, Point point, Direction direction, Faction faction, Master &master): Horde(map, point, direction, faction, master) {}

void Werewolf::normalAttack(Minion& other) {
    other.reduceLife(unirand::getValueAround(this->damages, 2));
}

void Werewolf::hurtItself() {
    this->reduceLife(unirand::getValueAround(this->selfDamages));
}