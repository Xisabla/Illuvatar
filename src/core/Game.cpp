/*=========================================================================

  Project:   Illuvatar
  File:      Game.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/Game.h"

#include "gui/MainWindow.h"
#include "map/Map.h"

#include <stdexcept>

//  --------------------------------------------------------------------------------------
//  Game
//  --------------------------------------------------------------------------------------

Game::Game(_token t, QApplication* app): Singleton(t), _app(app) {
    if (_app == nullptr)
        throw std::runtime_error(
        "Game::Game: Please provide a valid QApplication at first instantiation");

    Map::instance().generate();
}

//  --------------------------------------------------------------------------------------
//  Game > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Game::step() { std::cout << "[game] Step" << std::endl; }

void Game::run(int steps) {
    std::cout << "[game] Run" << std::endl;

    for (int i = 0; i < steps; i++) step();
}

int Game::exec() { return QApplication::exec(); }
