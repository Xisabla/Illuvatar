/*=========================================================================

Project:   Illuvatar
File:      Horde.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Horde.h"

using namespace std;

Horde::Horde(Map &map, Point point, Direction direction, Faction faction, Master &master): Minion(map, point, direction, faction, master) {}

void Horde::Meet(const Horde& hordeMinion) { }
void Horde::Meet(const Alliance& allianceMinion) { }
