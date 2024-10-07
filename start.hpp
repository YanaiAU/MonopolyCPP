#ifndef START_HPP
#define START_HPP

#include "square.hpp"
#include "player.hpp"

class Start : public Square {
public:
    Start(const std::string& name, int x, int y);
    void onPlayerLanding(Player& player) override;
};

#endif // START_HPP
