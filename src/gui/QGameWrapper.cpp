/*=========================================================================

  Project:   Illuvatar
  File:      QGameWrapper.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "gui/QGameWrapper.h"

#include "gui/QGameSidebar.h"
#include "map/Map.h"

#include <QHBoxLayout>

//  --------------------------------------------------------------------------------------
//  QGameWrapper
//  --------------------------------------------------------------------------------------

QGameWrapper::QGameWrapper(QWidget* parent)
: QWidget(parent), _qgmap(Map::instance().qgmap()), _qgsidebar(new QGameSidebar(this)) {
    auto layout = new QHBoxLayout;

    layout->addWidget(_qgmap);
    layout->addWidget(_qgsidebar);

    this->setLayout(layout);
}
