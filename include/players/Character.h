/*=========================================================================

Project:   Illuvatar
File:      Character.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_CHARACTER_H
#define ILLUVATAR_CHARACTER_H

#include "map/Map.h"
#include "wip.h"
#include "geometry/Point.h"

#include <list>
#include <string>
#include <vector>

class Map;

class Character {
  public:
    Character(Map &map, Point point, Faction faction);
    std::vector<std::string> GetMessageList();
    void SetMessageList(std::vector<std::string>& messageList);

    Point& getPoint() { return this->point; }

    Faction getFaction() { return this->faction; }

  protected:
    Map& map;
    Point point;
    Faction faction;

  private:
    std::vector<std::string> MessageList;
};


#endif // ILLUVATAR_CHARACTER_H
