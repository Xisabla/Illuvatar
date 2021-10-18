/*=========================================================================

Project:   Illuvatar
File:      MainWindow.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

#include "core/MainWindow.h"
#include "map/Map.h"

#include <QApplication>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    // Map
    Map map(10, 10);
    QGameMap gmap = map.toQGameMap();
    window.setCentralWidget(&gmap);

    return app.exec();
}
