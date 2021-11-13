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

Master::Master(unsigned int x, unsigned int y, Faction faction): Character(x, y, faction) {
    // TODO: Unsure that not other master exists
    messagesFaction = Environment::instance()->env()["characters"][strFromFaction.at(faction)]["master"]["messages"].get<std::vector<std::string>>();
    this->addMessages(messagesFaction);
}

//  --------------------------------------------------------------------------------------
//  Master > PUBLIC METHODS
//  --------------------------------------------------------------------------------------


std::string Master::getAssetPath() { return Character::getAssetPath() + "Master.png"; }

void Master::collectAndSendBack(Minion* minion) {
    //collect all
    if (minion->gotMsg()) {
        this->addMessages(minion->messages());
        minion->dropMessages();
    }
    minion->unsetNewMsg();

    //give one
    minion->addMessage(this->getRandomMessage());
}

void Master::addMessages(std::vector<std::string> messages) {
    auto itBegin = this->messages().begin();
    auto itEnd = this->messages().end();
    for (std::string message : messages) {
        if (std::find(itBegin, itEnd, message) == itEnd) continue;
        this->addMessage(message);
    }
}

std::string Master::getRandomMessage() {
    if (this->messagesFaction.empty()) throw std::runtime_error("Master faction message list is empty");

    return this->messagesFaction[unirand::getValue(0, static_cast<int>(this->messagesFaction.size()) - 1)];
}

void Master::printAction(std::string str) {
    std::cout << "Master " << this->faction() << ": " << str << std::endl;
}
