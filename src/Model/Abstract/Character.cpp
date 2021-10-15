#include "Character.h"

#include <utility>

std::list<std::string> Character::GetMessageList() {
    return MessageList;
}

void Character::SetMessageList(std::list<std::string> &messageList) {
    MessageList = std::move(messageList);
}
