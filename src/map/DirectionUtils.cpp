#include "map/DirectionUtils.h"

using namespace std;
using namespace directionutils;

ostream& directionutils::operator<<(ostream& out, const Direction value) {
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(Direction::N);
        PROCESS_VAL(Direction::NE);
        PROCESS_VAL(Direction::E);
        PROCESS_VAL(Direction::SE);
        PROCESS_VAL(Direction::S);
        PROCESS_VAL(Direction::SW);
        PROCESS_VAL(Direction::W);
        PROCESS_VAL(Direction::NW);
    }
#undef PROCESS_VAL

    return out << s;
}

Direction directionutils::computeDirection(const Tile &last, const Tile &current) {
    int deltaX = current.X() - last.X();
    int deltaY = current.Y() - last.Y();
    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        cout << "error at directionutils::computeDirection(" << deltaX << ", " << deltaY << ");" << endl;
        exit(1);
    }
    return deltaDirection.at({deltaX, deltaY});
}
