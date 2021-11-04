#include "map/DirectionUtils.h"

using namespace std;
using namespace directionutils;

Direction directionutils::computeDirection(const Point& last, const Point& current) {
    int deltaX = current.X() - last.X();
    int deltaY = current.Y() - last.Y();
    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        cout << "error at directionutils::computeDirection(" << deltaX << ", " << deltaY << ");"
             << endl;
        exit(1);
    }
    return deltaDirection.at({ deltaX, deltaY });
}

Point directionutils::computeLastJump(const Direction& direction) {
    return nextDirection.at(oppositeDirection.at(direction));
}
