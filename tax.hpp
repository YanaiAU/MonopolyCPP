#ifndef TAX_HPP
#define TAX_HPP

#include "square.hpp"
#include "player.hpp"

class Tax : public Square {
private:
    int amount;
public:
    Tax(const std::string& name, int x, int y, int amount);
    void onPlayerLanding(Player& player) override;
    int getTaxAmount();
};

#endif // TAX_HPP
