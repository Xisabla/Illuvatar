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
    messagesFaction = Environment::instance()->env()["characters"][strFromFaction.at(faction)]["master"]["messages"].get<std::vector<std::string>>();
    Character::addMessages(messagesFaction);
}

//  --------------------------------------------------------------------------------------
//  Master > PUBLIC METHODS
//  --------------------------------------------------------------------------------------


std::string Master::getAssetPath() { return Character::getAssetPath() + "Master.png"; }

void Master::collectAndSendBack(Minion* minion) {
    printAction("Reçoit minion");

    //collect all
    if (minion->gotMsg()) {
        printAction("Récupère ses messages");
        this->addMessages(minion->messages());
        minion->dropMessages();
    }
    minion->unsetNewMsg();

    //give one
    std::string msg = this->getRandomMessage();
    printAction("Lui confie le message "+msg);
    minion->addMessage(msg);
}

void Master::addMessages(std::vector<std::string> messages) {
    auto itBegin = this->messages().begin();
    auto itEnd = this->messages().end();
    for (std::string message : messages) {
        std::cout << "\t" << message << ": ";
        if (std::find(itBegin, itEnd, message) != itEnd) {
            std::cout << "Déjà connu..." << std::endl;
            continue;
        }
        std::cout << "Inconnu !" << std::endl;
        this->addMessage(message);
    }
}

std::string Master::getRandomMessage() {
    if (this->messagesFaction.empty()) throw std::runtime_error("Master faction message list is empty");

    return this->messagesFaction[unirand::getValue(0, static_cast<int>(this->messagesFaction.size()) - 1)];
}

void Master::printAction(std::string str) {
    std::cout << "[Master] " << this->faction() << ": " << str << std::endl;
}
