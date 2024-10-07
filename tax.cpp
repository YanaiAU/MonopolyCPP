#include "start.hpp"
#include "tax.hpp"

Tax::Tax(const std::string& name, int x, int y, int amount)
    : Square(name, x, y) {
    this->type = "Tax";
    this->amount = amount;
}

void Tax::onPlayerLanding(Player &player) {
    player.pay(amount);
}

int Tax::getTaxAmount(){
    return amount;
}
