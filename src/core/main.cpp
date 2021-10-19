/*=========================================================================

Project:   Illuvatar
File:      MainWindow.cpp

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

#include "core/MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Instantiate map
    Map map(10, 10);

    // Create and show window
    MainWindow window(map);
    window.show();

    // Synchronize map with graphical map widget
    map.syncGMap();

    // Example: set the color of point after the map is being synchronized (does repaint the
    // graphical object)
    map.GMap()->setPointColor(Point(5, 5), Qt::blue);

    return QApplication::exec();
}
