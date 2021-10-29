#include "map/DirectionUtils.h"

using namespace std;
using namespace directionutils;

Direction directionutils::computeDirection(const Tile &last, const Tile &current) {
    return deltaDirection.at({ current.X() - last.X(), current.Y() - last.Y() });
}
