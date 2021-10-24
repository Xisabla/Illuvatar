#include "model/abstract/Character.h"

#include <utility>

using namespace std;

std::list<std::string> Character::GetMessageList() {
    return MessageList;
}

void Character::SetMessageList(std::list<std::string> &messageList) {
    MessageList = std::move(messageList);
}
