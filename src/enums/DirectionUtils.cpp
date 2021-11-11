#include "enums/DirectionUtils.h"

using namespace std;
using namespace directionutils;

Direction directionutils::computeDirection(const superTypes::Point& last, const superTypes::Point& current) {
    int deltaX = current.first - last.first;
    int deltaY = current.second - last.second;
    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        cout << "error at directionutils::computeDirection(" << deltaX << ", " << deltaY << ");"
             << endl;
        exit(1);
    }
    return deltaDirection.at({ deltaX, deltaY });
}

superTypes::Point directionutils::computeLastJump(const Direction& direction) {
    return nextDirection.at(oppositeDirection.at(direction));
}

Direction directionutils::randDirection() {
    int index = unirand::getValue(static_cast<int>(Direction::DIRECTION_FIRST), static_cast<int>(Direction::DIRECTION_LAST));
    return static_cast<Direction>(index);
}