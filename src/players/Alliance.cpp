/*=========================================================================

Project:   Illuvatar
File:      Alliance.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Alliance.h"

using namespace std;

Alliance::Alliance(Map &map, Point point, Direction direction, Faction faction, Master &master): Minion(map, point, direction, faction, master) {}

void Alliance::Meet(const Horde& hordeMinion) { }
void Alliance::Meet(const Alliance& allianceMinion) { }
