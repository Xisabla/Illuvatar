/*=========================================================================

Project:   Illuvatar
File:      RollResult.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_ATTACKNATURE_H
#define ILLUVATAR_ATTACKNATURE_H

#include <string>
#include <map>

/**
 * @enum AttackNature
 * @brief physical or energical damages
 */
enum class AttackNature { Physical, Energetic };

const std::map<std::string, AttackNature> strToAttackNature = {
    {"Physical", AttackNature::Physical},
    {"Energetic", AttackNature::Energetic}
};

#endif // ILLUVATAR_ATTACKNATURE_H
