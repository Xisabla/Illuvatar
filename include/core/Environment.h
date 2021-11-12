/*=========================================================================

  Project:   Illuvatar
  File:      Environment.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "libs/json.h"

#include <string>

/**
 * @class Vala
 * @brief Short description of the class
 */
class Environment {
  public:
    static Environment* instance();
    nlohmann::json& env();

  private:
    static Environment* _instance;
    nlohmann::json _env;

    Environment(std::string filePath);
};

#endif // ENVIRONMENT_H
