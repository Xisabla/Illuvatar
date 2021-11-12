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

  public slots:
    void handleStepButton();
    void handleRunButton();
    void handleExitButton();
};

#endif // ILLUVATAR_QGAMESIDEBAR_H
