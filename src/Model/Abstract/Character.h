#ifndef ILLUVATAR_CHARACTER_H
#define ILLUVATAR_CHARACTER_H

#include <list>
#include <string>
#include<wip.h>

class Character {
  private:
    std::list<std::string> MessageList;

  public:
    Faction faction;

    std::list<std::string> GetMessageList();
    void SetMessageList(std::list<std::string> &messageList);
};


#endif // ILLUVATAR_CHARACTER_H
