#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <QLabel>
#include <vector>
#include "Square.hpp"
#include "street.hpp"
#include "railroad.hpp"
#include "utility"

class Square;

class Player {
private:
    std::string name;
    int x;
    int y;
    int boardIndex = 0;
    int money = 1500;
    int turnsInJail = 0;
    int doubleCount = 0;
    int numOfRailroads = 0;
    bool inJail = false;
    bool get_out_of_jail_card = false;
    std::vector<Square*> properties;
    int lastDiceResults;
    QLabel* label;

public:
    Player(const std::string &name, QLabel* label);

    void setPosition(int newX, int newY);
    void moveToSquare(Square &square);
    void moveToPosition(int newX, int newY);
    void addDiceResultsToBoardIndex(int results);
    void moveToJail();
    void move(int dice_roll);
    void pay(int amount);
    void earn(int amount);
    void buyProperty(Square &square);
    void payRent(Square &square);
    void payRent(int amount);
    void buildHouse(Street &street);
    void buildHotel(Street &street);
    void goToJail();
    void tryLeaveJail();
    void addNumOfRailroads();
    void setNumOfRailroads(int amount);

    int getX() const;
    int getY() const;
    int getMoney() const;
    int getBoardIndex() const;
    QLabel* getLabel() const;
    std::string getName() const;
    std::vector<Square*> getProperties() const;
    int getNumberOfRailroads() const;
    int getNumberOfUtilities() const;

    bool ownsAllPropertiesInColorGroup(const std::string& colorGroup);


    bool isInJail() const;
    int getTurnsInJail() const;
    void setIsInJail(bool inJail);
    bool hasGetOutOfJailCard() const;
    void receiveGetOutOfJailCard();
    void useGetOutOfJailCard();

    const int getLastDiceResults() const;
    void setLastDiceResults(int results);
};

#endif // PLAYER_HPP
