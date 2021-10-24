#include "map/DirectionUtils.h"

using namespace std;


Direction DirectionUtils::computeDirection(Tile* const &last, Tile* const &current) {
    return DirectionUtils::deltaDirection.at({ current->X() - last->X(), current->Y() - last->Y() });
}
