#ifndef JAIL_HPP
#define JAIL_HPP

#include "square.hpp"

class Jail : public Square {
public:
    Jail(const std::string &name, int x, int y);
    void onPlayerLanding(Player &player) override;
};

#endif // JAIL_HPP
