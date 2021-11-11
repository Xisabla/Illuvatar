/*=========================================================================

  Project:   Illuvatar
  File:      QGameMap.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_QGAMEMAP_H
#define ILLUVATAR_QGAMEMAP_H

#include "enums/Faction.h"

#include <QWidget>

// TODO: Link QGameMap to it's parent (QGameWrapper) to handle actions
//  process: QGameSidebar slot -> QGameWrapper method -> QGameMap method

/**
 * @class QGameMap
 * @brief Graphical Map as a Qt Object, draws and update the map.
 *  Act as the command receiver from QGameSidebar
 */
class QGameMap : public QWidget {
  public:
    explicit QGameMap(QWidget* parent = nullptr);

  private:
    // - Methods -----------------------------------------------------------------------------
    void paintEvent(QPaintEvent*) override;

    // - Attributes --------------------------------------------------------------------------
    static std::map<Faction, QImage> masterAssets;
    static std::map<Faction, QImage> minionAssets;
};

#endif // ILLUVATAR_QGAMEMAP_H
