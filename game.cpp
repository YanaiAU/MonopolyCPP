#include "game.hpp"
#include "chance.hpp"
#include "freeparking.hpp"
#include "gotojail.hpp"
#include "railroad.hpp"
#include "utility.hpp"
#include "street.hpp"
#include "start.hpp"
#include "tax.hpp"
#include "jail.hpp"
#include <cstdlib>
#include <ctime>

Game::Game() : currentTurn(0), diceIndex(0) {
    srand(static_cast<unsigned int>(time(nullptr)));

    createSquares();
}

Game::~Game() {
    for (Square* square : squares) {
        delete square;
    }

    for (Player* player : players) {
        delete player;
    }
}

int Game::JAIL_INDEX = 10;

void Game::createSquares() {
    QString squareNames[40] = {
        "Start", "Mediteranean Avenue", "Chance", "Baltic Avenue", "Income Tax",
        "Reading Railroad", "Oriental Avenue", "Chance", "Vermont Avenue", "Conneticut Avenue",
        "Jail", "St. Charles Place", "Electric Company", "States Avenue", "Virginia Avenue",
        "Pennsylvania Railroad", "St. James Place", "Chance", "Tennessee Avenue", "New York Avenue",
        "Free Parking", "Kentucky Avenue", "Chance", "Indiana Avenue", "Illinois Avenue", "B. & O. Railroad",
        "Atlantic Avenue", "Venitor Avenue", "Water Works", "Marvin Gardens", "Go To Jail", "Pacific Avenue",
        "North Carolina Avenue", "Chance", "Pennsylvania Avenue", "Short Line", "Chance",
        "Park Place", "Luxury Tax", "Boardwalk"
    };

    int streetPrices[40] = {
        0, 60, 0, 60, 0,
        200, 100, 0, 100, 120,
        0, 140, 150, 140, 160,
        200, 180, 0, 180, 200,
        0, 220, 0, 220, 240, 200,
        260, 260, 150, 280, 0, 300,
        300, 0, 320, 200, 0,
        350, 0, 400
    };

    QString streetColors[40] = {
        "", "brown", "", "brown", "",
        "", "light-blue", "", "light-blue", "light-blue",
        "", "pink", "", "pink", "pink",
        "", "orange", "", "orange", "orange",
        "", "red", "", "red", "red", "",
        "yellow", "yellow", "", "yellow", "", "green",
        "green", "", "green", "", "",
        "dark-blue", "", "dark-blue"
    };

    for (int i = 0; i < 40; ++i) {
        if (squareNames[i].contains("Chance")) {
            squares.push_back(new Chance(squareNames[i].toStdString(), 0, 0));
        } else if (squareNames[i] == "Income Tax") {
            squares.push_back(new Tax(squareNames[i].toStdString(), 0, 0, 200));
        }else if (squareNames[i] == "Luxury Tax"){
          squares.push_back(new Tax(squareNames[i].toStdString(), 0, 0, 100));
        } else if (squareNames[i].contains("Railroad") || squareNames[i] == "Short Line") {
            squares.push_back(new Railroad(squareNames[i].toStdString(), 0, 0, 200));
        } else if (squareNames[i].contains("Electric Company") || squareNames[i].contains("Water Works")) {
            squares.push_back(new Utility(squareNames[i].toStdString(), 0, 0, 150, 10));
        } else if (squareNames[i] == "Free Parking") {
            squares.push_back(new FreeParking(squareNames[i].toStdString(), 0, 0));
        } else if (squareNames[i] == "Go To Jail") {
            squares.push_back(new GoToJail(squareNames[i].toStdString(), 0, 0));
        } else if (squareNames[i] == "Jail") {
            squares.push_back(new Jail(squareNames[i].toStdString(), 0, 0));
        } else if (squareNames[i] == "Start") {
            squares.push_back(new Start(squareNames[i].toStdString(), 0, 0));
        } else {
            squares.push_back(new Street(squareNames[i].toStdString(), 0, 0, streetPrices[i], streetPrices[i]/4, streetPrices[i], streetPrices[i]*5 + 100, streetColors[i].toStdString()));
        }

        if ((i > 0 && i < 10) || (i > 20 && i < 30)) {
            squares[i]->setWidth(80);
            squares[i]->setHeight(100);
        } else if ((i > 10 && i < 20) || (i > 30 && i < 40)) {
            squares[i]->setWidth(100);
            squares[i]->setHeight(80);
        } else {
            squares[i]->setWidth(100);
            squares[i]->setHeight(100);
        }
    }
}


Square* Game::getSquare(int index) const {
    if (index >= 0 && index < static_cast<int>(squares.size())) {
        return squares[index];
    }
    return nullptr;
}

int Game::rollDice() {
    return (rand() % 6) + 1;
}

void Game::nextTurn() {
    currentTurn = (currentTurn % players.size()) + 1;
}

int Game::getCurrentTurn() const {
    return currentTurn;
}

void Game::nextPlayerTurn() {
    currentTurn = (currentTurn + 1) % players.size();
}

void Game::addPlayer(Player* player) {
    players.push_back(player);
}

void Game::increaseCornerSquareIndex(int lineIndex, int amount) {
    cornerSquareIndices[lineIndex] += amount;
}

std::vector<Player*>& Game::getPlayers() {
    return players;
}

std::vector<Square*>& Game::getSquares() {
    return squares;
}

void Game::buySquare() {
    Player* currentPlayer = getPlayers()[getCurrentTurn()];
    Square* currentSquare = getSquares()[currentPlayer->getBoardIndex()];

    currentPlayer->buyProperty(*currentSquare);
}

void Game::addSquare(const QString &name, const QString &type, int lineIndex, QLabel* label) {
    int lineStart = lineIndex * 10 + cornerSquareIndices[lineIndex];

    Square* newSquare = nullptr;
    if (type == "Utility") {
        newSquare = new Utility(name.toStdString(), 0, 0, 100, 4);
    } else if (type == "Railroad") {
        newSquare = new Railroad(name.toStdString(), 100, 300, 150);
    }

    int insertionIndex = lineIndex * 10 + cornerSquareIndices[lineIndex];
    squares.insert(squares.begin() + insertionIndex, newSquare);

    if (newSquare) {
        if (lineIndex == 0 || lineIndex == 2) {
            for (int i = lineStart; i < lineStart + 10; ++i) {
                squares[i]->setWidth(72);
                squares[i]->setHeight(100);
                if (lineIndex == 0) {
                    squares[i]->setX(squares[lineIndex * 10 + cornerSquareIndices[lineIndex] - 1]->getX() - (i - lineStart + 1) * 72);
                } else {
                    squares[i]->setX(squares[lineIndex * 10 + cornerSquareIndices[lineIndex] - 1]->getX() + (i - lineStart) * 72 + 100);
                }
                squares[i]->setY(squares[lineIndex * 10 + cornerSquareIndices[lineIndex] - 1]->getY());
            }
        } else {
            for (int i = lineStart; i < lineStart + 10; ++i) {
                squares[i]->setHeight(72);
                squares[i]->setWidth(100);
                if (lineIndex == 1) {
                    squares[i]->setY(squares[lineIndex * 10 + cornerSquareIndices[lineIndex] - 1]->getY() - (i - lineStart + 1) * 72);
                } else {
                    squares[i]->setY(squares[lineIndex * 10 + cornerSquareIndices[lineIndex] - 1]->getY() + (i - lineStart) * 72 + 100);
                }
                squares[i]->setX(squares[lineIndex * 10 + cornerSquareIndices[lineIndex] - 1]->getX());
            }
        }

        newSquare->setLabel(label);
        label->lower();

        for (int i = 0; i < static_cast<int>(players.size()); i++) {
            if (players[i]->getBoardIndex() >= insertionIndex) {
                players[i]->addDiceResultsToBoardIndex(1);
            }
        }
    }
    for (int i = lineIndex; i <= 3; i++) {
        increaseCornerSquareIndex(i, 1);
    }
}

int Game::getJailIndex(){
    return JAIL_INDEX;
}
void Game::setJailIndex(int newIndex){
    JAIL_INDEX = newIndex;
}
