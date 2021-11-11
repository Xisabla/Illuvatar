/*=========================================================================

  Project:   Illuvatar
  File:      Game.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_GAME_H
#define ILLUVATAR_GAME_H

#include "templates/Singleton.h"

#include <QApplication>

/**
 * @class Game
 * @brief Main object of the Simulation (aka Game), handles all the "high-level" actions, such as
 *  playing a step in the game loop or running the loop.
 *  This object is a Singleton as we only
 *  want one handler and no other one (as well as the Map object)
 *  Game also instantiates the Map, launch its generation, create the Minions and Masters in it's
 *  initialization process (constructor)
 */
SINGLETON(Game) {
  public:
    Game(_token t, QApplication * app);

    // - Getters -----------------------------------------------------------------------------
    static Game& instance(QApplication * app = nullptr) {
        static const std::unique_ptr<Game> instance { new Game { _token {}, app } };
        return *instance;
    }

    // - Methods -----------------------------------------------------------------------------
    void step();
    void run(int steps = 50);

    static int exec();

  private:
    // - Attributes --------------------------------------------------------------------------
    QApplication* _app;
};

#endif // ILLUVATAR_GAME_H
