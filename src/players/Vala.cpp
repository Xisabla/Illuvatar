/*=========================================================================

Project:   Illuvatar
File:      Vala.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Vala.h"

Vala::Vala(Map &map, Point point, Master &master): Alliance(map, point, Faction::Valars, master) {}
