/*=========================================================================

Project:   Illuvatar
File:      RollResult.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_ROLLRESULT_H
#define ILLUVATAR_ROLLRESULT_H

#include <iostream>

/**
 * @enum RollResult
 * @brief Available dice results in the simulation
 */
enum class RollResult { CriticalSuccess, Success, Failure, CriticalFailure };

#endif // ILLUVATAR_ROLLRESULT_H
