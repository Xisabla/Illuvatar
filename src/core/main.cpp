/*=========================================================================

  Project:   Illuvatar
  File:      main.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/Game.h"
#include "gui/MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    Game::instance(new QApplication(argc, argv));

    // Instantiate main window in main thread
    MainWindow window;
    window.show();

    return Game::exec();

    /**
     MAIN:

     Game game = Game::instance();
     game.start();
     -->
     Game::instance():

        QApplication
        QMainWindow
        -> QGameMap --> Map::instance() + map.link(QGameMap) OR Map::instance(QGameMap)
     <--

     IDEAS:

     Map == Singleton, Preset/MapPreset/MapGenerator = enum
     Map::setDefaultPreset(<preset>)
     Map map = Map::instance()
     map.regenerate(<preset>)

     ~Map() --> Tile::removeAll()

     map.sync() --> sync with QGameMap (emit signal ?)

     DRAW (QGameMap), naming conventions:
     x, y <=> Components
     rpx, rpy <=> "Relative Plaint x,y", absolute position on the canvas (= gpx - offset),
        only useful if there is a position grid on the side (chess like) that causes an offset
     apx, apy <=> "Absolute Paint x,y", true absolute position on the drawing
     > Have methods to convert x <=> rpx <=> apx
                               x <=========> apx

     */
}
