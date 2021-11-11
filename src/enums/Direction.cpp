#include "enums/Direction.h"

using namespace std;

ostream& operator<<(ostream& out, const Direction value) {
    const char* s = nullptr;
#define PROCESS_VAL(p) \
    case (p):          \
        s = #p;        \
        break;
    switch (value) {
        PROCESS_VAL(Direction::N)
        PROCESS_VAL(Direction::NE)
        PROCESS_VAL(Direction::E)
        PROCESS_VAL(Direction::SE)
        PROCESS_VAL(Direction::S)
        PROCESS_VAL(Direction::SW)
        PROCESS_VAL(Direction::W)
        PROCESS_VAL(Direction::NW)
    }
#undef PROCESS_VAL

    return out << s;
}
