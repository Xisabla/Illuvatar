/*=========================================================================

  Project:   Illuvatar
  File:      Map.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

/*=========================================================================

  Project:   Illuvatar
  File:      Map.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/

#pragma once
#ifndef ILLUVATAR_MAP_H
#define ILLUVATAR_MAP_H

#include <QWidget>
#include <QPainter>
#include <QLabel>

/**
 * @class Map
 * @brief Short description of the class
 */
class Map : public QWidget {
  public:
    Map(int width, int height, QWidget* parent = 0);

    // - Getters -----------------------------------------------------------------------------

    // - Setters -----------------------------------------------------------------------------

    // - Methods -----------------------------------------------------------------------------

    // - Friends -----------------------------------------------------------------------------

  private:
    // - Methods -----------------------------------------------------------------------------
    void paintEvent(QPaintEvent *);

    // - Attributes --------------------------------------------------------------------------
    int width;
    int height;
};


#endif // ILLUVATAR_MAP_H
