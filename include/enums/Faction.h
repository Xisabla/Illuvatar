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
#include <string>
#include <map>

/**
 * @enum Faction
 * @brief Available Factions in the simulation
 */
enum class Faction { Eldars, Valars, Dragons, Werewolves, NoFaction };

std::ostream& operator<<(std::ostream& out, Faction value);

/**
 * @brief Transform a Faction into a string
 */
const std::map<Faction, std::string> strFaction = {
    { Faction::Eldars, "Eldars" },
    { Faction::Valars, "Valars" },
    { Faction::Dragons, "Dragons" },
    { Faction::Werewolves, "Werewolves" }
};

#endif // ILLUVATAR_FACTION_H
