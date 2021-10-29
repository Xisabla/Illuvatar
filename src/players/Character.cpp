#include "players/Character.h"


using namespace std;

vector<string> Character::GetMessageList() { return MessageList; }

void Character::SetMessageList(vector<string>& messageList) {
    MessageList = move(messageList);
}
