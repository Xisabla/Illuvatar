#include "enums/Faction.h"

using namespace std;

ostream& operator<<(ostream& out, const Faction value) {
    const char* s = nullptr;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(Faction::Eldars)
        PROCESS_VAL(Faction::Valars)
        PROCESS_VAL(Faction::Dragons)
        PROCESS_VAL(Faction::Werewolves)
        PROCESS_VAL(Faction::NoFaction)
    }
#undef PROCESS_VAL

    return out << s;
}
