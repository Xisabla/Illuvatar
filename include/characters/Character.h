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
    [[nodiscard]] std::vector<std::string> messages() const;

    // - Setters -----------------------------------------------------------------------------
    void setMessages(std::vector<std::string> messages);

    // - Methods -----------------------------------------------------------------------------
    bool isAllied(Character* character);
    bool isMaster();

  protected:
    // - Methods -----------------------------------------------------------------------------
    void addMessage(const std::string& message);
    void addMessages(std::vector<std::string> messages);
    std::string getRandomMessage();
    std::string dropRandomMessage();
    void dropMessages();

    // - Attributes -------------------------------------------------------------------------
    unsigned int _x;
    unsigned int _y;
    Faction _faction;

  private:
    // - Attributes --------------------------------------------------------------------------
    std::vector<std::string> _messages;

    static std::map<Faction, std::set<Faction>> alliances;
};


#endif // ILLUVATAR_CHARACTER_H
