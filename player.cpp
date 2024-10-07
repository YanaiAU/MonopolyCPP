#include "player.hpp"
#include "street.hpp"
#include "railroad.hpp"
#include "utility.hpp"
#include "game.hpp"
#include <QTimer>

Player::Player(const std::string &name, QLabel* label)
    : name(name), x(0), y(0), label(label) {
}

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::move(int dice_roll) {
    if (inJail) {
        if (turnsInJail < 3) {
            turnsInJail++;
            if (dice_roll % 2 == 0) {
                doubleCount++;
                if (doubleCount == 2) {
                    inJail = false;
                    turnsInJail = 0;
                    doubleCount = 0;
                }
            }
            return;
        } else {
            pay(50);
            inJail = false;
            turnsInJail = 0;// LOOOKAT THIS!!!FEW3224422435-------PPPPPP
            doubleCount = 0;
            return;
        }
    }

    int previousBoardIndex = boardIndex;
    addDiceResultsToBoardIndex(dice_roll);
    if(previousBoardIndex > boardIndex){
        earn(200);
    }
}

void Player::addDiceResultsToBoardIndex(int results) {
    boardIndex = (boardIndex + results) % 40;
}

void Player::moveToSquare(Square &square) {
    setPosition(square.getX(), square.getY());
    if (label) {
        label->move(getX(), getY());}}

void Player::moveToPosition(int newX, int newY) {
    setPosition(newX, newY);
    label->move(newX, newY);
}

int Player::getX() const { return x; }

int Player::getY() const { return y; }

int Player::getMoney() const { return money; }

int Player::getBoardIndex() const { return boardIndex; }

std::string Player::getName() const { return name; }

QLabel* Player::getLabel() const { return label; }

std::vector<Square*> Player::getProperties() const { return properties; }

void Player::earn(int amount) {
    money += amount;
}

void Player::pay(int amount) {
    if (money >= amount) {
        money -= amount;
    } else {
        // Bankruptcy - to add later.
    }
}

void Player::buyProperty(Square &square) {
    if (square.getType() == "Street") {
        Street* street = static_cast<Street*>(&square);
        if (money >= street->getPrice() && street->getOwner() == nullptr) {
            pay(street->getPrice());
            properties.push_back(&square);
            street->setOwner(this);
        }
    } else if (square.getType() == "Railroad") {
        Railroad* railroad = static_cast<Railroad*>(&square);
        if (money >= railroad->getPrice() && railroad->getOwner() == nullptr) {
            pay(railroad->getPrice());
            properties.push_back(&square);
            railroad->setOwner(this);
        }
    } else if (square.getType() == "Utility") {
        Utility* utility = static_cast<Utility*>(&square);
        if (money >= utility->getPrice() && utility->getOwner() == nullptr) {
            pay(utility->getPrice());
            properties.push_back(&square);
            utility->setOwner(this);
        }
    }
}

void Player::payRent(Square &square) {
    Player* owner = nullptr;

    if (square.getType() == "Street") {
        Street* street = static_cast<Street*>(&square);
        owner = street->getOwner();
        if (owner && owner != this) {
            pay(street->getRent());
            owner->earn(street->getRent());
        }
    } else if (square.getType() == "Railroad") {
        Railroad* railroad = static_cast<Railroad*>(&square);
        owner = railroad->getOwner();
        if (owner && owner != this) {
            pay(railroad->getRent());
            owner->earn(railroad->getRent());
        }
    } else if (square.getType() == "Utility") {
        Utility* utility = static_cast<Utility*>(&square);
        owner = utility->getOwner();
        if (owner && owner != this) {
            int diceRoll = getLastDiceResults(); //REMEMBER TO MAKE SURE IT'SS FINE
            pay(utility->getRent(diceRoll));
            owner->earn(utility->getRent(diceRoll));
        }
    }
}

void Player::buildHouse(Street &street) {
    if (ownsAllPropertiesInColorGroup(street.getColorGroup()) && street.canBuildHouse()) {
        pay(street.getHousePrice());
        street.buildHouse();
    }
}

void Player::addNumOfRailroads(){
    setNumOfRailroads(getNumberOfRailroads() + 1);
}

void Player::buildHotel(Street &street) {
    if (ownsAllPropertiesInColorGroup(street.getColorGroup()) && street.getNumHouses() == 4) {
        pay(street.getHotelPrice());
        street.buildHotel();
    }
}

bool Player::ownsAllPropertiesInColorGroup(const std::string& colorGroup) { // NOT WORKINNG YET NEED TO FIX
    int count = 0;
    int totalInGroup = 0;
    for (Square* property : properties) {
        if (property->getType() == "Street") {
            Street* street = static_cast<Street*>(property);
            if (street->getColorGroup() == colorGroup) {
                count++;
            }
        }
    }
    totalInGroup = 3;
    return count == totalInGroup;
}

void Player::payRent(int amount){
    money -= amount;
}

void Player::receiveGetOutOfJailCard() {
    get_out_of_jail_card = true;
}

void Player::useGetOutOfJailCard() {
    get_out_of_jail_card = true;
}

bool Player::hasGetOutOfJailCard() const {
    return get_out_of_jail_card;
}

int Player::getNumberOfRailroads() const {
    int count = 0;
    for (Square* property : properties) {
        if (property->getType() == "Railroad") {
            count++;
        }
    }
    return count;
}

void Player::setNumOfRailroads(int amount){
    numOfRailroads = amount;
}

const int Player::getLastDiceResults() const {
    return lastDiceResults;
}

void Player::setLastDiceResults(int results){
    lastDiceResults = results;
}

void Player::moveToJail(){
    boardIndex = Game::getJailIndex();

    int jailX = 0;
    int jailY = 850;

    int centerX = jailX + 25;
    int centerY = jailY + 25;

    QTimer::singleShot(100, [this, centerX, centerY]() {
        moveToPosition(centerX, centerY);
    });

    inJail = true;
}

void Player::setIsInJail(bool inJail){
    inJail = inJail;
}

bool Player::isInJail() const{
    return inJail;
}
