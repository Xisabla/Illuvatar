/*=========================================================================

  Project:   Illuvatar
  File:      MainWindow.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

#pragma once
#ifndef ILLUVATAR_MAINWINDOW_H
#define ILLUVATAR_MAINWINDOW_H

#include <QMainWindow>
#include "map/Map.h"

/**
 * @class MainWindow
 * @brief Short description of the class
 */
class MainWindow : public QMainWindow {
  public:
    /**
     * @param map Map of the game
     */
    MainWindow(Map map);
};

#endif // ILLUVATAR_MAINWINDOW_H
