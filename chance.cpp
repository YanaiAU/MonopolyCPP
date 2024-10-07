#include "Chance.hpp"
#include "Player.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

static const std::string chanceOptions[] = {
    "Collect $200",
    "Get out of jail card",
    "Pay poor tax of $120"
};

Chance::Chance(const std::string& name, int x, int y) : Square(name, x, y) {
    type = "Chance";
}

void Chance::pickRandomChance() {
    int randomIndex = std::rand() % 3;
    chanceText = chanceOptions[randomIndex];
}

void Chance::onPlayerLanding(Player &player) {
    pickRandomChance();
    std::cout << "Player " << player.getName() << " landed on Chance! Card: " << chanceText << std::endl;

    if (chanceText == "Collect $200") {
        player.earn(200);
    } else if (chanceText == "Get out of jail card") {
        player.receiveGetOutOfJailCard();
    } else if (chanceText == "Pay poor tax of $120") {
        player.pay(120);
    }
}

std::string Chance::getChanceText() const {
    return chanceText;
}
