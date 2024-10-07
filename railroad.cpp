#include "railroad.hpp"
#include "player.hpp"

Railroad::Railroad(const std::string &name, int x, int y, int price)
    : Square(name, x, y), price(price), owner(nullptr) {
    this->type = "Railroad";
}

void Railroad::onPlayerLanding(Player &player) {
    if (owner && owner != &player) {
        int currentRent = getRent();
        player.payRent(currentRent);
        owner->earn(currentRent);
    }
}

int Railroad::getPrice() const {
    return price;
}

bool Railroad::isOwned() const {
    return owner != nullptr;
}

Player* Railroad::getOwner() const {
    return owner;
}

void Railroad::setOwner(Player* newOwner) {
    owner = newOwner;
}

int Railroad::getRent() const {
    if (owner) {
        int numOwned = owner->getNumberOfRailroads();
        return rent * numOwned;
    }
    return 0;
}

Railroad::~Railroad() {}
