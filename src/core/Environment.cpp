/*=========================================================================

  Project:   Illuvatar
  File:      Master.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/Environment.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

Environment* Environment::_instance= nullptr;

Environment::Environment(std::string filePath) {
    std::ifstream t(filePath, std::ios::in);
    t.seekg(0);
    _env = nlohmann::json::parse((std::istreambuf_iterator<char>(t)), (std::istreambuf_iterator<char>()));
}

Environment* Environment::instance() {
    if(Environment::_instance==nullptr) {
        std::string projectName = "Illuvatar";

        std::string path_string = fs::current_path().string();
        auto pos = path_string.find(projectName);
        if (pos == std::string::npos) {
            std::cout << "Game folder not found!" << std::endl;
            exit(1);
        }
        std::string sub = path_string.substr(pos+projectName.size());
        if (sub[sub.size()-1] != '/') path_string += "/";
        for (int i = 0; i < std::count(sub.begin(), sub.end(), '/'); ++i) path_string += "../";
        path_string += "build/environment.json";

        Environment::_instance = new Environment(path_string);
    }
    return _instance;
}

nlohmann::json& Environment::env() {
    return _env;
}
