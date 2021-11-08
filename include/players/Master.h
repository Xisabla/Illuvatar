/*=========================================================================

  Project:   Illuvatar
  File:      Master.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_MASTER_H
#define ILLUVATAR_MASTER_H

#include "players/Minion.h"
#include "map/Map.h"
#include "players/Character.h"

class Minion;

class Master : public Character {
  public:
    Master(Map& map, Point point, Faction faction, std::vector<std::string> &listOfBaseMessage);
    void getMessage(Minion& minion);
    void giveMessage(Minion& minion);
    Master static compareSize(Master& masterOne, Master& masterTwo);

  private:
    std::set<std::string> listOfMessage;
    std::vector<std::string> MessageToGive;
};


#endif // ILLUVATAR_MASTER_H
