#include "jail.hpp"

Jail::Jail(const std::string &name, int x, int y)
    : Square(name, x, y) {
    type = "Jail";
}

void Jail::onPlayerLanding(Player &player) {
}
