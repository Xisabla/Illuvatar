/*=========================================================================

  Project:   Illuvatar
  File:      uniformRandom.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_UNIRAND_H
#define ILLUVATAR_UNIRAND_H

#include <iterator>
#include <random>
#include <chrono>

namespace unirand {
    /**
     * @brief Draw a value among an uniform distribution of values
     * @param min The included inferior bound
     * @param max The included superior bound
     * @return A value between specified bounds
     */
    int getValue(int min, int max);

    /**
     * @brief Get more or less of the value with uniform random choice
     * @param value The reference value
     * @param range The maximum potential of more or less
     * @return A value around given
     */
    int getValueAround(int value, int range=1);
}

#endif // ILLUVATAR_UNIRAN_H
