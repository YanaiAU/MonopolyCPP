#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <string>
#include <QLabel>

class Player;

class Square {
protected:
    std::string name;
    std::string type;
    int x;
    int y;
    int width;
    int height;
    QLabel* label;

public:
    Square(const std::string &name, int x, int y);
    virtual void onPlayerLanding(Player &player) = 0;
    virtual ~Square();

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    std::string getName() const;
    std::string getType() const;
    QLabel* getLabel() const;

    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int width);
    void setLabel(QLabel* newLabel);
};

#endif // SQUARE_HPP
