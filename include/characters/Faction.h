/*=========================================================================

  Project:   Illuvatar
  File:      Faction.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_FACTION_H
#define ILLUVATAR_FACTION_H

#include <map>
#include <set>

/**
 * @enum Faction
 * @brief Available Factions in the simulation
 */
enum Faction { NoFaction, Dragons, Eldars, Valars, Werewolves };

/**
 * @brief All alliances between factions
 */
// TODO: Move to Character ? + isAllied(Character)
/*
 std::map<Faction, std::set<Faction>> Alliances = { { Eldars, { Eldars, Valars } },
                                                   { Valars, { Eldars, Valars } },
                                                   { Werewolves, { Dragons, Werewolves } },
                                                   { Dragons, { Dragons, Werewolves } } };
                                                   */

#endif // ILLUVATAR_FACTION_H
