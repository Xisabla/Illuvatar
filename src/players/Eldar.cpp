/*=========================================================================

Project:   Illuvatar
File:      Eldar.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Eldar.h"

Eldar::Eldar(Map &map, Point point, Master &master): Alliance(map, point, Faction::Eldars, master) {}
