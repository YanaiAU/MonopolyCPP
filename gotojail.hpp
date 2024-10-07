#ifndef GOTJAIL_HPP
#define GOTJAIL_HPP

#include "square.hpp"

class GoToJail : public Square {
public:
    GoToJail(const std::string &name, int x, int y);
    void onPlayerLanding(Player &player) override;
};

#endif // GOTJAIL_HPP
