#include "wip.h"

std::ostream& operator<<(std::ostream& out, const ThingAtPoint value) {
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(ThingAtPoint::Void);
        PROCESS_VAL(ThingAtPoint::Nothing);
        PROCESS_VAL(ThingAtPoint::Obstacle);
        PROCESS_VAL(ThingAtPoint::Ennemy);
        PROCESS_VAL(ThingAtPoint::Ally);
    }
#undef PROCESS_VAL

    return out << s;
}
