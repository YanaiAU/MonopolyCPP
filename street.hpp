#ifndef STREET_HPP
#define STREET_HPP

#include "Square.hpp"
#include <string>
#include <vector>

class Player;

class Street : public Square {
private:
    int price;
    Player* owner;
    int rent;
    int housePrice;
    int hotelPrice;
    int numHouses = 0;
    bool hasHotel = false;
    std::string colorGroup;
    std::vector<Street*> sameGroupStreets;

public:
    Street(const std::string &name, int x, int y, int price, int rent, int housePrice, int hotelPrice, const std::string& colorGroup);

    void onPlayerLanding(Player &player) override;

    int getPrice() const;
    bool isOwned() const;
    Player* getOwner() const;
    void setOwner(Player* newOwner);

    bool canBuildHouse() const;
    void buildHouse();
    void buildHotel();
    bool getHasHotel() const;
    int getRent() const;

    int getHousePrice() const;
    int getHotelPrice() const;
    int getNumHouses() const;

    std::string getColorGroup() const;

    void setSameGroupStreets(const std::vector<Street*>& streets);

    ~Street();
};

#endif // STREET_HPP
