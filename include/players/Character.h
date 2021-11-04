/*=========================================================================

Project:   Illuvatar
File:      Character.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_CHARACTER_H
#define ILLUVATAR_CHARACTER_H

#include "enums/Faction.h"
#include "map/Map.h"
#include "geometry/Point.h"
#include "unirand.h"

#include <list>
#include <string>
#include <vector>


class Character {
  public:
    Character(Map& map, Point point, Faction faction);
    void setMsgList(std::vector<std::string>& msgList);
    std::vector<std::string>& getMsgList();

    Point& getPoint() { return this->point; }

    Faction getFaction() { return this->faction; }

  protected:
    Map& map;
    Point point;
    Faction faction;

    void addMsg(std::string msg);
    void addMsgList(std::vector<std::string>& msgList);
    std::string getRandomMsg();
    std::string dropRandomMsg();
    void dropMsgList();

  private:
    std::vector<std::string> msgList;
};

#endif // ILLUVATAR_CHARACTER_H
