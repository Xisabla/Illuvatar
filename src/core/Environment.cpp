/*=========================================================================

  Project:   Illuvatar
  File:      Master.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/Environment.h"

#include <fstream>

Environment* Environment::_instance= nullptr;

Environment::Environment(std::string filePath) {
    std::ifstream t(filePath, std::ios::in);
    t.seekg(0);
    _env = nlohmann::json::parse((std::istreambuf_iterator<char>(t)), (std::istreambuf_iterator<char>()));
}

Environment* Environment::instance() {
    if(Environment::_instance==nullptr){
        Environment::_instance = new Environment("environment.json");//"../build/environment.json"
    }
    return _instance;
}

nlohmann::json& Environment::env() {
    return _env;
}
