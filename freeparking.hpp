#ifndef FREEPARKING_HPP
#define FREEPARKING_HPP

#include "square.hpp"

class FreeParking : public Square {
public:
    FreeParking(const std::string &name, int x, int y);
    void onPlayerLanding(Player &player);
};

#endif // FREEPARKING_HPP
