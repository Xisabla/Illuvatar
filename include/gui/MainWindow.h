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

/**
 * @class MainWindow
 * @brief Basically the main Simulation Window, starts in fullscreen
 */
class MainWindow : public QMainWindow {
  public:
    MainWindow();
};

#endif // ILLUVATAR_MAINWINDOW_H