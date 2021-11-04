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

    /**
     * @brief Heritable destructor who removes the character from his tile (disappears from the map)
     */
    virtual ~Character();

    /**
     * @brief Set all Character messages
     */
    void setMsgList(std::vector<std::string>& msgList);
    
    /**
     * @brief Gives all Character messages
     */
    std::vector<std::string>& getMsgList();

    /**
     * @brief Gives Character current position
     */
    Point& getPoint() { return this->point; }

    /**
     * @brief Gives Character faction
     */
    Faction getFaction() { return this->faction; }

  protected:
    Map& map;
    Point point;
    Faction faction;

    /**
     * @brief Add one message to the list
     * @param msg Message to add
     */
    void addMsg(std::string msg);
    
    /**
     * @brief Add multiple messages to the list
     * @param msgList Messages to add
     */
    void addMsgList(std::vector<std::string>& msgList);
    
    /**
     * @brief Give one message from the list
     */
    std::string getRandomMsg();
    
    /**
     * @brief Extract one message from the list
     */
    std::string dropRandomMsg();

    /**
     * @brief Remove all messages of the list
     */
    void dropMsgList();

  private:
    /**
     * @brief List of messages to deal with
     */
    std::vector<std::string> msgList;
};

#endif // ILLUVATAR_CHARACTER_H
