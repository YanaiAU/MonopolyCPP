#ifndef CHANCE_HPP
#define CHANCE_HPP

#include "Square.hpp"
#include <string>

class Chance : public Square {
private:
    std::string chanceText;

    void pickRandomChance();

public:
    Chance(const std::string& name, int x, int y);

    void onPlayerLanding(Player &player) override;

    std::string getChanceText() const;
};

#endif // CHANCE_HPP
