#include "map/DirectionUtils.h"

using namespace std;
using namespace DirectionUtils;


Direction computeDirection(Tile* const &last, Tile* const &current) {
    return deltaDirection.at({ current->X() - last->X(), current->Y() - last->Y() });
}
