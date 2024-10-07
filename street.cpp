#include "street.hpp"
#include "player.hpp"

Street::Street(const std::string &name, int x, int y, int price, int rent, int housePrice, int hotelPrice, const std::string& colorGroup)
    : Square(name, x, y), price(price), owner(nullptr), rent(rent), housePrice(housePrice), hotelPrice(hotelPrice), numHouses(0), hasHotel(false), colorGroup(colorGroup) {
    this->type = "Street";
}

void Street::onPlayerLanding(Player &player) {
    if (owner && owner != &player) {
        int currentRent = getRent();
        player.payRent(currentRent);
        owner->earn(currentRent);
    }
}

int Street::getPrice() const {
    return price;
}

bool Street::isOwned() const {
    return owner != nullptr;
}

Player* Street::getOwner() const {
    return owner;
}

void Street::setOwner(Player* newOwner) {
    owner = newOwner;
}

bool Street::canBuildHouse() const {
    for (Street* street : sameGroupStreets) {
        if (street->getOwner() != owner) return false;
    }
    return numHouses < 4 && !hasHotel;
}

void Street::buildHouse() {
    if (canBuildHouse()) {
        numHouses++;
    }
}

void Street::buildHotel() {
    if (numHouses == 4 && !hasHotel) {
        hasHotel = true;
        numHouses = 0;
    }
}

int Street::getRent() const {
    if (hasHotel) {
        return hotelPrice;
    } else if (numHouses > 0) {
        return rent * (1 << (numHouses - 1));
    } else {
        return rent;
    }
}

bool Street::getHasHotel() const{
    return hasHotel;
}

std::string Street::getColorGroup() const {
    return colorGroup;
}

void Street::setSameGroupStreets(const std::vector<Street*>& streets) {
    sameGroupStreets = streets;
}

Street::~Street() {}

int Street::getHousePrice() const { return housePrice; }
int Street::getHotelPrice() const { return hotelPrice; }
int Street::getNumHouses() const { return numHouses; }
