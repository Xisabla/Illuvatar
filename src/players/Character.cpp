#include "players/Character.h"


using namespace std;

Character::Character(Map &map, Tile &Tile, Faction faction): map(map), tile(tile), faction(faction) {}

vector<string> Character::GetMessageList() { return MessageList; }

void Character::SetMessageList(vector<string>& messageList) {
    MessageList = move(messageList);
}
