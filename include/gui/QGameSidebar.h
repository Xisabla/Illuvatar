/*=========================================================================

  Project:   Illuvatar
  File:      QGameSidebar.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_QGAMESIDEBAR_H
#define ILLUVATAR_QGAMESIDEBAR_H

// TODO: Link QGameSidebar to it's parent (QGameWrapper) to send actions
//  process: QGameSidebar slot -> QGameWrapper method -> QGameMap method

#include <QPushButton>
#include <QWidget>

/**
 * @class QGameSidebar
 * @brief Graphical wrapper that contains all Game inputs (buttons, fields, ...).
 *  Act as the command invoker for QGameMap
 */
class QGameSidebar : public QWidget {
    Q_OBJECT

  public:
    explicit QGameSidebar(QWidget* parent = nullptr);
    void enableButtons();
    void disableButtons();

  public slots:
    void handleStepButton();
    void handleRunButton();
    void handleResetButton();
    void handleExitButton();

  private:
    QPushButton* _stepButton;
    QPushButton* _runButton;
};

#endif // ILLUVATAR_QGAMESIDEBAR_H
