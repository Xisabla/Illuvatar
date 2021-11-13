/*=========================================================================

  Project:   Illuvatar
  File:      Character.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/Character.h"

#include "characters/Master.h"
#include "map/Map.h"
#include "unirand.h"

#include <stdexcept>

//  --------------------------------------------------------------------------------------
//  Character
//  --------------------------------------------------------------------------------------

std::map<Faction, Faction> Character::alliance = {
    { Faction::Eldars, Faction::Valars },
    { Faction::Valars, Faction::Eldars },
    { Faction::Dragons, Faction::Werewolves },
    { Faction::Werewolves, Faction::Dragons },
};

Character::Character(unsigned int x, unsigned int y, Faction faction)
: _x(x), _y(y), _faction(faction) {
    Map::instance().linkCharacter(x, y, this);
}

Character::~Character() { Map::instance().unlinkCharacter(this); }

//  --------------------------------------------------------------------------------------
//  Character > GETTERS
//  --------------------------------------------------------------------------------------

unsigned int Character::x() const { return _x; }

unsigned int Character::y() const { return _y; }

Faction Character::faction() const { return _faction; }

std::vector<std::string> Character::messages() const { return _messages; }

//  --------------------------------------------------------------------------------------
//  Character > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

// bool Character::isAllied(Character* character) {
//     return alliances[_faction].contains(character->faction());
// }

bool Character::isMaster() { return dynamic_cast<Master*>(this) != nullptr; }

void Character::dropMessages() { _messages.clear(); }

bool Character::gotMsg() { return !this->_messages.empty(); }

std::string Character::getAssetPath() { return strFromFaction.at(this->_faction) + "/"; }

//  --------------------------------------------------------------------------------------
//  Character > PROTECTED METHODS
//  --------------------------------------------------------------------------------------

void Character::addMessage(const std::string& message) { _messages.push_back(message); }

void Character::addMessages(std::vector<std::string> messages) {
    std::move(messages.begin(), messages.end(), std::back_inserter(_messages));
}

std::string Character::getRandomMessage() {
    if (_messages.empty()) throw std::runtime_error("Character message list is empty");

    return _messages[unirand::getValue(0, static_cast<int>(_messages.size()) - 1)];
}

std::string Character::dropRandomMessage() {
    if (_messages.empty()) throw std::runtime_error("Character message list is empty");

    int i = unirand::getValue(0, static_cast<int>(_messages.size()) - 1);
    std::string msg = _messages[i];

    std::remove(_messages.begin(), _messages.end(), msg);

    return msg;
}

bool Character::gotOneMsg() { return this->_messages.size() == 1; }

