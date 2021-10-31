#include "players/Character.h"


using namespace std;

Character::Character(Map &map, Point point, Faction faction): map(map), point(point), faction(faction) {}

vector<string> Character::GetMessageList() { return MessageList; }

void Character::SetMessageList(vector<string>& messageList) {
    MessageList = move(messageList);
}
