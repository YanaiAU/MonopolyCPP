#include "square.hpp"
#include "player.hpp"

Square::Square(const std::string &name, int x, int y)
    : name(name), x(x), y(y), width(0), height(0), label(nullptr) {}

Square::~Square() {
    delete label;
}

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}

int Square::getWidth() const {
    return width;
}

int Square::getHeight() const {
    return height;
}

std::string Square::getName() const {
    return name;
}

std::string Square::getType() const {
    return type;
}

QLabel* Square::getLabel() const {
    return label;
}

void Square::setX(int x) {
    this->x = x;
}

void Square::setY(int y) {
    this->y = y;
}

void Square::setWidth(int width) {
    this->width = width;
}

void Square::setHeight(int height) {
    this->height = height;
}

void Square::setLabel(QLabel* newLabel) {
    if (label != nullptr) {
        delete label;
    }
    label = newLabel;
}
