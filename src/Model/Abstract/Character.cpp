#include "model/abstract/Character.h"

#include <utility>

using namespace std;

std::vector<std::string> Character::GetMessageList() { return MessageList; }

void Character::SetMessageList(vector<string>& messageList) {
    MessageList = std::move(messageList);
}
