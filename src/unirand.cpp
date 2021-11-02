#include "unirand.h"

int unirand::getValue(int min, int max) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); // could be generalized but compilo angry
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(generator);
}