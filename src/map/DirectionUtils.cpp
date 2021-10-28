#include "map/DirectionUtils.h"

using namespace std;
using namespace directionutils;

Direction computeDirection(const Tile &last, const Tile &current) {
    return deltaDirection.at({ current.X() - last.X(), current.Y() - last.Y() });
}
