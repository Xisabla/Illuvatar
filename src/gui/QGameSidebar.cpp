/*=========================================================================

  Project:   Illuvatar
  File:      QGameSidebar.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "gui/QGameSidebar.h"

#include "core/Game.h"
#include "map/Map.h"

#include <QApplication>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

//  --------------------------------------------------------------------------------------
//  QGameSidebar
//  --------------------------------------------------------------------------------------

QGameSidebar::QGameSidebar(QWidget* parent): QWidget(parent) {
    auto layout = new QVBoxLayout;

    auto stepButton = new QPushButton("Step");
    auto runButton = new QPushButton("Run");
    auto separator = new QFrame;
    auto exitButton = new QPushButton("Exit");

    // Link buttons to actions
    QObject::connect(stepButton, SIGNAL(clicked()), this, SLOT(handleStepButton()));
    QObject::connect(runButton, SIGNAL(clicked()), this, SLOT(handleRunButton()));
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(handleExitButton()));

    separator->setFrameShape(QFrame::HLine);

    layout->setAlignment(Qt::AlignVCenter);
    layout->addWidget(stepButton);
    layout->addWidget(runButton);
    layout->addWidget(separator);
    layout->addWidget(exitButton);

    this->setLayout(layout);
    this->setMaximumWidth(200);
}

//  --------------------------------------------------------------------------------------
//  QGameSidebar > SLOTS
//  --------------------------------------------------------------------------------------

void QGameSidebar::handleStepButton() { Game::instance().step(); }

void QGameSidebar::handleRunButton() { Game::instance().run(); }

void QGameSidebar::handleExitButton() { QApplication::exit(0); }
