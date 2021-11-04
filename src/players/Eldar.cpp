/*=========================================================================

Project:   Illuvatar
File:      Eldar.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Eldar.h"

using namespace std;

Eldar::Eldar(Map &map, Point point, Direction direction, Faction faction, Master &master): Alliance(map, point, direction, faction, master) {}
