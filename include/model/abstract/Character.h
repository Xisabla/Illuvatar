/*=========================================================================

Project:   Illuvatar
File:      Character.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_CHARACTER_H
#define ILLUVATAR_CHARACTER_H

#include "map/Map.h"
#include "wip.h"

#include <list>
#include <string>
#include <vector>

class Character {
  private:
    std::vector<std::string> MessageList;

  public:
    Map* map;
    Tile* tile;
    Faction faction;

    std::vector<std::string> GetMessageList();
    void SetMessageList(std::vector<std::string>& messageList);
};


#endif // ILLUVATAR_CHARACTER_H
