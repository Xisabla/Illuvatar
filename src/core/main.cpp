/*=========================================================================

  Project:   Illuvatar
  File:      main.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/Game.h"
#include "core/Environment.h"
#include "gui/MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    Game::instance(new QApplication(argc, argv));

    // Instantiate main window in main thread
    MainWindow window;
    window.show();

    return Game::exec();
}
