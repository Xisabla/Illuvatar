/*=========================================================================

  Project:   Illuvatar
  File:      unirand.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "unirand.h"

#include <chrono>
#include <random>

int unirand::getValue(int min, int max) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(min, max);

    return distrib(generator);
}

int unirand::getValueAround(int value, int range) {
    return unirand::getValue(value - range, value + range);
}