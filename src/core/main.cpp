/*=========================================================================

Project:   Illuvatar
File:      MainWindow.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

#include <QApplication>
#include "core/main_window.h"
#include "map/map.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MainWindow window;

    Map map(10, 10);
    window.setCentralWidget(&map);

    window.show();

    return app.exec();

}