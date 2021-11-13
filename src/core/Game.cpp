/*=========================================================================

  Project:   Illuvatar
  File:      Game.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/Game.h"

#include "characters/BadMinion.h"
#include "characters/GoodMinion.h"
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

void Game::step(QGameSidebar* qgsidebar, bool doesEnable) {
    // prend tous les minions et les fait move
    qgsidebar->disableButtons();

    std::cout << "[game] Step" << std::endl;
    for (auto characterEntry: Map::instance().characters()) {
        Character* character = characterEntry.second;
        auto minion = dynamic_cast<Minion*>(character);
        if (minion != nullptr) {
            minion->move();
        }
        //Map::instance().sync();
    }

    if (doesEnable) qgsidebar->enableButtons();
}

void Game::run(QGameSidebar* qgsidebar, int maxSteps) {
    std::cout << "[game] Run" << std::endl;

    for (int i = 0; i < maxSteps; i++) {
        step(qgsidebar, false);
        if (end()) break;
    }

    qgsidebar->enableButtons();
}

bool Game::end() {
    bool stillGoodMinion = false;
    bool stillBadMinion = false;
    for (auto characterEntry: Map::instance().characters()) {
        Character* character = characterEntry.second;

        if (dynamic_cast<GoodMinion*>(character) != nullptr) stillGoodMinion = true;
        else if (dynamic_cast<BadMinion*>(character) != nullptr)
            stillBadMinion = true;

        if (stillGoodMinion && stillBadMinion) return false;
    }
    return true;
}

int Game::exec() { return QApplication::exec(); }

void Game::reset() {
    Map::instance().removeAllCharacters();
    Map::instance().generate();
};
