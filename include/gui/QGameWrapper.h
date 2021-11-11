/*=========================================================================

  Project:   Illuvatar
  File:      QGameWrapper.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_QGAMEWRAPPER_H
#define ILLUVATAR_QGAMEWRAPPER_H
// TODO: Link "child" components
//  process: QGameSidebar slot -> QGameWrapper method -> QGameMap method

#include <QWidget>
#include "gui/QGameMap.h"
#include "gui/QGameSidebar.h"

/**
 * @class QGameWrapper
 * @brief A simple Qt object to wrap main components to run the simulation (QGameMap, QGameSidebar),
 *  Act as a "controller" to pass commands from QGameSidebar to QGameMap
 */
class QGameWrapper : public QWidget {
  public:
    explicit QGameWrapper(QWidget* parent = nullptr);
  private:
    // - Attributes --------------------------------------------------------------------------
    QGameMap* _qgmap;
    QGameSidebar* _qgsidebar;
};

#endif // ILLUVATAR_QGAMEWRAPPER_H
