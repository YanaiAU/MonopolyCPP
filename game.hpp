#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <QPoint>
#include "Square.hpp"
#include "player.hpp"

class Game{
public:
    Game();
    ~Game();

    void createSquares();
    Square* getSquare(int index) const;
    int rollDice();
    void nextTurn();
    int getCurrentTurn() const;
    void nextPlayerTurn();
    void addPlayer(Player* player);
    void addSquare(const QString &name, const QString &type, int lineIndex, QLabel* label);
    void increaseCornerSquareIndex(int lineIndex, int amount);
    void buySquare();
    std::vector<Player*>& getPlayers();
    std::vector<Square*>& getSquares();
    static int getJailIndex();
    static void setJailIndex(int newIndex);
private:
    int currentTurn;
    int diceIndex;
    int cornerSquareIndices[4] = {1, 1, 1, 1};
    std::vector<Square*> squares;
    std::vector<Player*> players;
    static int JAIL_INDEX;
};

#endif // GAME_HPP
