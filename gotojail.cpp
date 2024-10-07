#include "gotojail.hpp"
#include "player.hpp"

GoToJail::GoToJail(const std::string &name, int x, int y)
    : Square(name, x, y) {
    type = "GoToJail";
}

void GoToJail::onPlayerLanding(Player &player) {
    player.setIsInJail(true);
    player.moveToJail();
}
