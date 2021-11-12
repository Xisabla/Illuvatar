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

#include <string>
#include <vector>
#include <set>

/**
 * @class Character
 * @brief Short description of the class
 */
class Character {
  public:
    Character(unsigned int x, unsigned int y, Faction faction);
    virtual ~Character();

    // - Getters -----------------------------------------------------------------------------
    [[nodiscard]] unsigned int x() const;
    [[nodiscard]] unsigned int y() const;
    [[nodiscard]] Faction faction() const;
    [[nodiscard]] std::vector<std::string> messages() const;//std::vector<std::string>& getMsgList();

    // - Setters -----------------------------------------------------------------------------
    void setMessages(std::vector<std::string> messages);//void setMsgList(std::vector<std::string>& msgList);

    // - Methods -----------------------------------------------------------------------------
    // bool isAllied(Character* character);
    bool isMaster();
    void dropMessages();
    bool gotMsg();
    virtual std::string getAssetPath();
    void addMessage(const std::string& message);

  protected:
    // - Methods -----------------------------------------------------------------------------
    virtual void addMessages(std::vector<std::string> messages);
    virtual std::string getRandomMessage();
    std::string dropRandomMessage();
    bool gotOneMsg();
    [[maybe_unused]] bool gotLotOfMsgs();

    // - Attributes -------------------------------------------------------------------------
    unsigned int _x;
    unsigned int _y;
    Faction _faction;
    static std::map<Faction, Faction> alliance;

  private:
    // - Attributes --------------------------------------------------------------------------
    std::vector<std::string> _messages;
};


#endif // ILLUVATAR_CHARACTER_H
