#ifndef RAILROAD_HPP
#define RAILROAD_HPP

#include "Square.hpp"

class Player;

class Railroad : public Square {
private:
    int price;
    Player* owner;
    int rent = 50;

public:
    Railroad(const std::string &name, int x, int y, int price);

    void onPlayerLanding(Player &player) override;

    int getPrice() const;
    bool isOwned() const;
    Player* getOwner() const;
    void setOwner(Player* newOwner);
    int getRent() const;

    ~Railroad();
};

#endif // RAILROAD_HPP
