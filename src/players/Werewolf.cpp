/*=========================================================================

Project:   Illuvatar
File:      Werewolf.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "players/Werewolf.h"

Werewolf::Werewolf(Map &map, Point point, Master &master): Horde(map, point, Faction::Werewolves, master) {}
