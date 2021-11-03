/*=========================================================================

Project:   Illuvatar
File:      Faction.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_FACTION_H
#define ILLUVATAR_FACTION_H

#include <iostream>

/**
 * @enum Faction
 * @brief Available Factions in the simulation
 */
enum Faction { Eldars, Valars, Dragons, Werewolves, NoFaction };

std::ostream& operator<<(std::ostream& out, Faction value);

#endif // ILLUVATAR_FACTION_H
