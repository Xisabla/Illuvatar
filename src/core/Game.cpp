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
    counter = 0;
}

//  --------------------------------------------------------------------------------------
//  Game > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void Game::step(QGameSidebar* qgsidebar, bool doesEnable) {
    if (end(qgsidebar)) return;

    qgsidebar->disableButtons();
    std::cout << std::endl << std::endl << std::endl << std::endl << "[game] Time step " << counter++ << std::endl;

    auto charList = Map::instance().characters();
    for (auto characterEntry: charList) {
        Minion* minion = dynamic_cast<Minion*>(characterEntry.second);
        if (minion == nullptr || !minion->isAlive()) continue;

        std::cout << std::endl;
        minion->printAction();
        minion->move();
        if (!minion->isAlive()) {
            Map::instance().unlinkCharacter(minion);
            Map::instance().sync();
        }
    }

    for (auto characterEntry: charList) {
        Minion* minion = dynamic_cast<Minion*>(characterEntry.second);
        if (minion == nullptr) continue;
        if (!minion->isAlive()) delete minion;
    }

    if (doesEnable) qgsidebar->enableButtons();
}

void Game::run(QGameSidebar* qgsidebar, int maxSteps) {
    qgsidebar->disableButtons();
    std::cout << "[game] Run" << std::endl;

    for (int i = 0; i < maxSteps; i++) {
        step(qgsidebar, false);
        if (end(qgsidebar)) return;
    }

    qgsidebar->enableButtons();
}

bool Game::end(QGameSidebar* qgsidebar) {
    bool stillGoodMinion = false;
    bool stillBadMinion = false;
    // for (auto characterEntry: Map::instance().characters()) {
    //     Character* character = characterEntry.second;

    //     Minion* minion = dynamic_cast<Minion*>(characterEntry.second);
    //     if (minion == nullptr || !minion->isAlive()) continue;

    //     if (dynamic_cast<GoodMinion*>(character) != nullptr) stillGoodMinion = true;
    //     else if (dynamic_cast<BadMinion*>(character) != nullptr) stillBadMinion = true;

    //     if (stillGoodMinion && stillBadMinion) {
    //         std::cout << "[game] Game not finished yet !" << std::endl;
    //         return false;
    //     }
    // }

    std::cout << "[game] End of the game ! Victory for " << (stillGoodMinion ? "GoodMinions!" : "BadMinions!") << std::endl;
    qgsidebar->disableButtons();
    return true;
}

int Game::exec() { return QApplication::exec(); }

void Game::reset(QGameSidebar* qgsidebar) {
    Map::instance().removeAllCharacters();
    counter = 0;
    std::cout.width(25);
    std::cout.fill('\n');
    std::cout.flush();
    Map::instance().generate();
    qgsidebar->enableButtons();
};
