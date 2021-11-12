/*=========================================================================

  Project:   Illuvatar
  File:      QGameSidebar.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "gui/QGameSidebar.h"

#include "core/Game.h"

#include <QApplication>
#include <QFrame>
#include <QVBoxLayout>
#include <iostream>

//  --------------------------------------------------------------------------------------
//  QGameSidebar
//  --------------------------------------------------------------------------------------

QGameSidebar::QGameSidebar(QWidget* parent): QWidget(parent) {
    auto layout = new QVBoxLayout;

    _stepButton = new QPushButton("Step");
    _runButton = new QPushButton("Run");
    auto separator = new QFrame;
    auto exitButton = new QPushButton("Exit");

    // Link buttons to actions
    QObject::connect(_stepButton, SIGNAL(clicked()), this, SLOT(handleStepButton()));
    QObject::connect(_runButton, SIGNAL(clicked()), this, SLOT(handleRunButton()));
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(handleExitButton()));

    separator->setFrameShape(QFrame::HLine);

    layout->setAlignment(Qt::AlignVCenter);
    layout->addWidget(_stepButton);
    layout->addWidget(_runButton);
    layout->addWidget(separator);
    layout->addWidget(exitButton);

    this->setLayout(layout);
    this->setMaximumWidth(200);
}

//  --------------------------------------------------------------------------------------
//  QGameSidebar > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void QGameSidebar::disableButtons() {
    _stepButton->setDisabled(true);
    _runButton->setDisabled(true);
}

void QGameSidebar::enableButtons() {
    _stepButton->setDisabled(false);
    _runButton->setDisabled(false);
}

//  --------------------------------------------------------------------------------------
//  QGameSidebar > SLOTS
//  --------------------------------------------------------------------------------------

void QGameSidebar::handleStepButton() { Game::instance().step(this); }

void QGameSidebar::handleRunButton() { Game::instance().run(this); }

void QGameSidebar::handleExitButton() { QApplication::exit(0); }
