#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Square.hpp"

class Player;

class Utility : public Square {
private:
    int price;
    Player* owner;
    int multiplier = 1;
    int lastDiceRoll;

public:
    Utility(const std::string &name, int x, int y, int price, int multiplier);

    void onPlayerLanding(Player &player) override;

    int getPrice() const;
    bool isOwned() const;
    Player* getOwner() const;
    void setOwner(Player* newOwner);
    int getLastDiceRoll() const;
    int getRent(int diceRoll) const;

    ~Utility();
};

#endif // UTILITY_HPP
