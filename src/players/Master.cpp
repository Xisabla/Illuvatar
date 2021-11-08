#include "players/Master.h"

#include <utility>

using namespace std;

Master::Master(Map &map, Point point, Faction faction, vector<string> &listOfBaseMessage)
: Character(map, point, faction) {
    listOfMessage = {};
    MessageToGive = listOfBaseMessage;
}

/// Méthode à appeler en cas de rencontre en minion et master de même faction.
void Master::getMessage(Minion& minion) {
    /// On récupère les messages des minions avec des messages.
    if (!minion.gotMsg()) return;

    listOfMessage.insert(minion.getMsgList().begin(),minion.getMsgList().end());
    minion.dropMsgList();
}

void Master::giveMessage(Minion& minion) {
    /// On set les messages du minions avec ceux que le master veut transmettre.
    minion.setMsgList(MessageToGive);
}

/// retourne le master qui possède le plus de message
Master Master::compareSize(Master& masterOne, Master& masterTwo) {
    return masterOne.listOfMessage.size() > masterTwo.listOfMessage.size() ? masterOne : masterTwo;
}
