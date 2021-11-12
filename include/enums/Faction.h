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
enum class Faction { NoFaction, Eldars, Valars, Dragons, Werewolves };

std::ostream& operator<<(std::ostream& out, Faction value);

/**
 * @brief Transform a Faction into a string
 */
const std::map<Faction, std::string> strFromFaction = {
    { Faction::Eldars, "Eldar" },
    { Faction::Valars, "Vala" },
    { Faction::Dragons, "Dragon" },
    { Faction::Werewolves, "Werewolf" }
};

const std::map<std::string, Faction> strToFaction = {
    { "Eldar", Faction::Eldars },
    { "Vala", Faction::Valars },
    { "Dragon", Faction::Dragons },
    { "Werewolf", Faction::Werewolves }
};

#endif // ILLUVATAR_FACTION_H
