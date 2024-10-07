#include "freeparking.hpp"

FreeParking::FreeParking(const std::string &name, int x, int y)
    : Square(name, x, y) {
    type = "FreeParking";
}

void FreeParking::onPlayerLanding(Player &player) {}
