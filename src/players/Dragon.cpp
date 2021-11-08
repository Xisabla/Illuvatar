/*=========================================================================

Project:   Illuvatar
File:      Dragon.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Dragon.h"

Dragon::Dragon(Map &map, Point point, Master &master): Horde(map, point, Faction::Dragons, master) {}
