#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include "addsquarewindow.h"
#include "game.hpp"
#include "qpushbutton.h"
#include "qtextedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void startRollingDice();
    void updateDiceImage();
    void stopRollingDice();
    void animatePlayerMove(Player* player, int steps);
    void openAddSquareWindow();
    void onBuyButtonClicked();
    void updateSquareLabels();
    void updatePlayerInfo();
    void updateSquareInfo(Player* player);

private:
    void initializeBoard();
    QPoint getSquarePosition(int index);
    void onSquareAdded(int index);

    Ui::MainWindow *ui;
    Game *game;
    QGraphicsScene *scene;
    AddSquareWindow *dialog = new AddSquareWindow(this);
    QTimer *rollTimer;
    QTimer *stopTimer;
    std::vector<QLabel*> squareLabels;
    int currentIndex = 0;
    QPushButton *AddSquareButton;
    QPushButton *buySquareButton;
    QTextEdit *playerInfoTextEdit;
    QTextEdit *squareInfoTextEdit;
    QLabel *SquareLimitLabel;
};

#endif // MAINWINDOW_HPP
