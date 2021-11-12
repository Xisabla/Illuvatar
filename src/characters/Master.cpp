/*=========================================================================

  Project:   Illuvatar
  File:      Master.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/Master.h"

//  --------------------------------------------------------------------------------------
//  Master
//  --------------------------------------------------------------------------------------

Master::Master(unsigned int x, unsigned int y, Faction faction, std::vector<std::string> listOfBaseMessage): Character(x, y, faction), MessageToGive(listOfBaseMessage), listOfMessage({}) {
    // TODO: Unsure that not other master exists
}

//  --------------------------------------------------------------------------------------
//  Master > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

std::string Master::generateMessage() { return "hello world :D"; }

std::string Master::getAssetPath() { return Character::getAssetPath() + "Master.png"; }

void Master::getMessage(Minion* minion) {
    /// On récupère les messages des minions avec des messages.
    if (!minion->gotMsg()) return;

    listOfMessage.insert(minion->messages().begin(),minion->messages().end());
    minion->dropMessages();
}

void Master::giveMessage(Minion* minion) {
    /// On set les messages du minions avec ceux que le master veut transmettre.
    minion->setMessages(MessageToGive);
}