#include "start.hpp"
#include "player.hpp"

Start::Start(const std::string& name, int x, int y)
    : Square(name, x, y) {
    this->type = "Start";
}

void Start::onPlayerLanding(Player &player) {
    // We are not adding 200$ because the player needs to receive
    // the money if passing the square, not only if landing on it.
    // This is taken care of in Player "move" function.
}
