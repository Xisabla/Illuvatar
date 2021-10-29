/*=========================================================================

  Project:   Illuvatar
  File:      MainWindow.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "core/MainWindow.h"

#include <QPushButton>
#include <QVBoxLayout>

// <-- Temporary object for demo
class RunnerTab : public QWidget {
  public:
    RunnerTab(Map map) {
        this->setLayout(new QVBoxLayout);

        this->layout()->addWidget(new QPushButton("Toggle coordinates"));
        this->layout()->addWidget(map.GMap());
    }
};

class MyTab : public QWidget {
  public:
    MyTab(int width, int height): width(width), height(height) { }

  private:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));

        painter.drawRect(0, 0, width, height);
    }

    int width, height;
};
// Temporary object for demo -->

//  --------------------------------------------------------------------------------------
//  MainWindow
//  --------------------------------------------------------------------------------------
MainWindow::MainWindow(Map map) {
    // TODO: Resize dynamically fitting screen size
    this->setMinimumSize(1280, 720);
    this->setMaximumSize(1920, 1080);

    // Tabs
    auto* tabWidget = new QTabWidget;

    tabWidget->addTab(new RunnerTab(map), tr("Runner"));
    tabWidget->addTab(new MyTab(200, 200), tr("Second tab"));

    this->setCentralWidget(tabWidget);
}
