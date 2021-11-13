/*=========================================================================

  Project:   Illuvatar
  File:      MainWindow.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "gui/MainWindow.h"

#include "gui/QGameWrapper.h"

#include <QHBoxLayout>

//  --------------------------------------------------------------------------------------
//  MainWindow
//  --------------------------------------------------------------------------------------

MainWindow::MainWindow() {
    // this->setWindowState(Qt::WindowFullScreen);
    this->setMinimumSize(1280, 720);
    this->setMaximumSize(1920, 1080);
    this->setCentralWidget(new QGameWrapper);
}
