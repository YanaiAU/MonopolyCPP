#include "utility.hpp"
#include "player.hpp"

Utility::Utility(const std::string &name, int x, int y, int price, int multiplier)
    : Square(name, x, y), price(price), owner(nullptr), multiplier(multiplier) {
    this->type = "Utility";
}

void Utility::onPlayerLanding(Player &player) {
    lastDiceRoll = player.getLastDiceResults();
    if (owner && owner != &player) {
        int currentRent = getRent(lastDiceRoll);
        player.payRent(currentRent);
        owner->earn(currentRent);
    }
}

int Utility::getPrice() const {
    return price;
}

bool Utility::isOwned() const {
    return owner != nullptr;
}

Player* Utility::getOwner() const {
    return owner;
}

int Utility::getLastDiceRoll() const{
    return lastDiceRoll;
}

void Utility::setOwner(Player* newOwner) {
    owner = newOwner;
}

int Utility::getRent(int diceRoll) const {
    return diceRoll * multiplier;
}

Utility::~Utility() {}
