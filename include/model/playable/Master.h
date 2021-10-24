#ifndef ILLUVATAR_MASTER_H
#define ILLUVATAR_MASTER_H

#include "Character.h"
#include "Minion.h"
#include "../Tools/Factions.h"

class Master : public Character
{
  public:
    Factions faction;

    std::string GetMessage(Minion &minion);
    void GiveMessage(Minion &minion);
};


#endif // ILLUVATAR_MASTER_H
