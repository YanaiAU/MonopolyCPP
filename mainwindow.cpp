#include "mainwindow.hpp"
#include "playerselectiondialog.h"
#include "ui_MainWindow.h"
#include <QGuiApplication>
#include <QRandomGenerator>
#include <QPixmap>
#include <QScreen>
#include <QMessageBox>
#include "game.hpp"
#include "player.hpp"
#include "chance.hpp"
#include "utility.hpp"
#include "start.hpp"
#include "tax.hpp"
#include "freeparking.hpp"
#include "addsquarewindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), game(new Game()) {

    PlayerSelectionDialog selectionDialog(this);
    selectionDialog.setModal(true);

    ui->setupUi(this);

    if (selectionDialog.exec() == QDialog::Accepted) {
        int numberOfPlayers = selectionDialog.getNumberOfPlayers();

        for (int i = 0; i < numberOfPlayers; ++i) {
            QString playerName = QString("Player %1").arg(i + 1);
            QLabel* playerLabel = findChild<QLabel *>(QString("player_%1").arg(i + 1));

            Player* player = new Player(playerName.toStdString(), playerLabel);

            game->addPlayer(player);
            playerLabel->setVisible(true);
        }
        for (int i = numberOfPlayers; i < 8; ++i) {
            QLabel* playerLabel = findChild<QLabel *>(QString("player_%1").arg(i + 1));
            playerLabel->setVisible(false);
        }
    } else {
        exit(EXIT_FAILURE);
    }

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = ((screenGeometry.height() - height()) / 2) - 50;
    move(x, y);

    AddSquareButton = ui->AddSquareButton;
    buySquareButton = ui->buySquareButton;
    SquareLimitLabel = ui->SquareLimitLabel;

    playerInfoTextEdit = ui->playerInfoTextEdit;
    playerInfoTextEdit->setReadOnly(true);
    squareInfoTextEdit = ui->squareInfoTextEdit;
    squareInfoTextEdit->setReadOnly(true);

    connect(ui->diceButton, &QPushButton::clicked, this, &MainWindow::startRollingDice);
    connect(AddSquareButton, &QPushButton::clicked, this, &MainWindow::openAddSquareWindow);
    connect(buySquareButton, &QPushButton::clicked, this, &MainWindow::onBuyButtonClicked);

    rollTimer = new QTimer(this);
    connect(rollTimer, &QTimer::timeout, this, &MainWindow::updateDiceImage);

    stopTimer = new QTimer(this);
    connect(stopTimer, &QTimer::timeout, this, &MainWindow::stopRollingDice);


    initializeBoard();
    updateSquareLabels();
    updateSquareInfo(game->getPlayers()[game->getCurrentTurn()]);
    updatePlayerInfo();
}

MainWindow::~MainWindow() {
    delete ui;
    delete game;
    delete dialog;
}

void MainWindow::initializeBoard() {
    auto& gameSquares = game->getSquares();

    squareLabels.clear();
    squareLabels.reserve(40);

    for (int i = 0; i < 40; ++i) {
        QString squareName = QString("square_%1").arg(i + 1);
        QLabel* label = findChild<QLabel *>(squareName);

        squareLabels.push_back(label);

        if (label) {
            int x = label->x();
            int y = label->y();

            gameSquares[i]->setX(x);
            gameSquares[i]->setY(y);
            gameSquares[i]->setLabel(label);

        } else {
            qWarning() << "Could not find" << squareName;
        }
    }
}


void MainWindow::startRollingDice() {
    game->nextPlayerTurn();
    rollTimer->start(50);
    stopTimer->start(400);
}

void MainWindow::updateDiceImage() {
    currentIndex = (currentIndex + 1) % 6;
    ui->diceLabel->setPixmap(QPixmap(QString(":/new/Images/resources/dice%1.png").arg(currentIndex + 1)));
    currentIndex = (currentIndex + 1) % 6;
    ui->diceLabel_2->setPixmap(QPixmap(QString(":/new/Images/resources/dice%1.png").arg(currentIndex + 1)));
}

void MainWindow::stopRollingDice() {
    rollTimer->stop();
    stopTimer->stop();

    int firstDiceRandomResult = game->rollDice();
    int secondDiceRandomResult = game->rollDice();
    ui->diceLabel->setPixmap(QPixmap(QString(":/new/Images/resources/dice%1.png").arg(firstDiceRandomResult)));
    ui->diceLabel_2->setPixmap(QPixmap(QString(":/new/Images/resources/dice%1.png").arg(secondDiceRandomResult)));

    Player* currentPlayer = game->getPlayers()[game->getCurrentTurn()];

    if(currentPlayer->isInJail()){
        if(firstDiceRandomResult == secondDiceRandomResult){
            currentPlayer->setIsInJail(false);
            currentPlayer->ge//fwergfwergwrg
        }else{
            return;
        }
    }

    int steps = firstDiceRandomResult + secondDiceRandomResult;
    currentPlayer->setLastDiceResults(steps);

    animatePlayerMove(currentPlayer, steps);
    currentPlayer->move(steps);

    game->getSquares()[currentPlayer->getBoardIndex()]->onPlayerLanding(*currentPlayer);

    updatePlayerInfo();
    updateSquareInfo(currentPlayer);
}

void MainWindow::animatePlayerMove(Player* player, int steps) {
    int startIndex = player->getBoardIndex();
    int targetIndex = (startIndex + steps) % game->getSquares().size();

    QTimer* animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [this, player, startIndex, targetIndex, animationTimer]() mutable {
        if (startIndex == targetIndex) {
            animationTimer->stop();
            animationTimer->deleteLater();
            return;
        }

        startIndex = (startIndex + 1) % game->getSquares().size();
        Square* nextSquare = game->getSquares()[startIndex];

        int squareX = nextSquare->getX();
        int squareY = nextSquare->getY();

        int offsetX = QRandomGenerator::global()->bounded(-10, 11);
        int offsetY = QRandomGenerator::global()->bounded(-10, 11);

        int centerX = squareX + offsetX + 25;
        int centerY = squareY + offsetY + 25;

        if(nextSquare->getType() == "GoToJail" && startIndex == targetIndex){
            player->moveToJail();
            int squareX = 0;
            int squareY = 900;

            int centerX = squareX + offsetX + 25;
            int centerY = squareY + offsetY + 25;
        }

        player->moveToPosition(centerX, centerY);
        player->getLabel()->raise();
    });

    animationTimer->start(100);
}

void MainWindow::onBuyButtonClicked() {
    Player* currentPlayer = game->getPlayers()[game->getCurrentTurn()];
    game->buySquare();
    updatePlayerInfo();
    updateSquareInfo(currentPlayer);
}

void MainWindow::openAddSquareWindow() {
    if (!dialog) {
        dialog = new AddSquareWindow(this);
        dialog->setModal(true);
    }

    if (dialog->exec() == QDialog::Accepted) {
        QString squareType = dialog->getSquareType();
        QString squareName = dialog->getSquareName();
        int lineIndex = dialog->getSelectedLine();

        QLabel* label = new QLabel(this);
        QPixmap pixmap(":/new/Images/resources/green_player.png");
        label->setPixmap(pixmap);
        label->setVisible(true);
        label->setObjectName("newLabel");

        game->addSquare(squareName, squareType, lineIndex, label);

        if (static_cast<int>(squareLabels.size()) <= lineIndex) {
            squareLabels.resize(lineIndex + 1);
        }
        squareLabels[lineIndex] = label;

        updateSquareLabels();
        for(size_t i = 0; i < game->getPlayers().size(); i++){
            Player* player = game->getPlayers()[i];
            QLabel* label = player->getLabel();
            player->moveToPosition(game->getSquares()[player->getBoardIndex()]->getX() + 25, game->getSquares()[player->getBoardIndex()]->getY() + 25);
            if (label) {
                label->move(player->getX(), player->getY());
            } else {
                qWarning() << "Label not found for square:" << player->getName();
            }
        }
    }
}

void MainWindow::updateSquareLabels() {
    const auto& squares = game->getSquares();

    for (size_t i = 0; i < squares.size(); ++i) {
        Square* square = squares[i];
        QLabel* label = square->getLabel();
        if (label) {
            label->setFixedWidth(square->getWidth());
            label->setFixedHeight(square->getHeight());
            label->move(square->getX(), square->getY());
        } else {
            qWarning() << "Label not found for square:" << square->getName();
        }
    }
}

void MainWindow::updatePlayerInfo() {
    QString text;
    const auto& players = game->getPlayers();

    for (size_t i = 0; i < players.size(); ++i) {
        Player* player = players[i];

        text += QString("Player %1:\n").arg(i + 1);
        text += QString("Money: %1\n").arg(player->getMoney());
        text += QString("Properties owned:\n");

        const auto& properties = player->getProperties();
        if (properties.empty()) {
            text += "No properties owned\n";
        } else {
            for (const auto& property : properties) {
                text += QString("%1 - %2\n")
                            .arg(QString::fromStdString(property->getName()))
                            .arg(QString::fromStdString(property->getType()));

                if (property->getType() == "Street") {
                    Street* street = dynamic_cast<Street*>(property);
                    if (street) {
                        // Print rent
                        text += QString("  Rent: %1\n").arg(street->getRent());
                        if (street->getHasHotel()) {
                            text += "  Hotel built\n";
                        } else {
                            int houseCount = street->getNumHouses();
                            text += QString("  Houses: %1\n").arg(houseCount);
                        }
                    }
                }
                else if (property->getType() == "Utility") {
                    Utility* utility = dynamic_cast<Utility*>(property);
                    if (utility) {
                        text += QString("  Rent: player's last dice roll * 10\n");
                    }
                }
                // If the property is a Railroad, show rent
                else if (property->getType() == "Railroad") {
                    Railroad* railroad = dynamic_cast<Railroad*>(property);
                    if (railroad) {
                        text += QString("  Rent: %1\n").arg(railroad->getRent());
                    }
                }
            }
        }
        if (player->hasGetOutOfJailCard()) {
            text += QString("This player has a Get out of jail card\n");
        }

        text += "\n\n";
    }

    playerInfoTextEdit->setPlainText(text);
}


void MainWindow::updateSquareInfo(Player* player) {
    int currentSquareIndex = player->getBoardIndex();
    Square* currentSquare = game->getSquare(currentSquareIndex);

    QString text;
    text += QString("Type: %1\n").arg(QString::fromStdString(currentSquare->getType()));

    std::string type = currentSquare->getType();

    if (type == "Street") {
        text += QString("Name: %1\n").arg(QString::fromStdString(currentSquare->getName()));
        Street* street = static_cast<Street*>(currentSquare);
        Player* owner = street->getOwner();

        if (owner) {
            text += QString("Owner: %1\n").arg(QString::fromStdString(owner->getName()));
        } else {
            text += "Owner: Not owned\n";
        }
        text += QString("Price: %1\n").arg(street->getPrice());
        text += QString("Rent: %1\n").arg(street->getRent());
        text += QString("House Price: %1\n").arg(street->getHousePrice());
        text += QString("Number of Houses: %1\n").arg(street->getNumHouses());
    } else if (type == "Railroad") {
        text += QString("Name: %1\n").arg(QString::fromStdString(currentSquare->getName()));
        Railroad* railroad = static_cast<Railroad*>(currentSquare);
        Player* owner = railroad->getOwner();

        if (owner) {
            text += QString("Owner: %1\n").arg(QString::fromStdString(owner->getName()));
        } else {
            text += "Owner: Not owned\n";
        }
        text += QString("Price: %1\n").arg(railroad->getPrice());
        text += QString("Rent: %1\n").arg(railroad->getRent());
    } else if (type == "Utility") {
        text += QString("Name: %1\n").arg(QString::fromStdString(currentSquare->getName()));
        Utility* utility = static_cast<Utility*>(currentSquare);
        Player* owner = utility->getOwner();

        if (owner) {
            text += QString("Owner: %1\n").arg(QString::fromStdString(owner->getName()));
        } else {
            text += "Owner: Not owned\n";
        }
        text += QString("Price: %1\n").arg(utility->getPrice());
        text += QString("Rent: %1\n").arg(utility->getRent(player->getLastDiceResults()));
    }else if (type == "Chance") {
        Chance* chance = static_cast<Chance*>(currentSquare);
        text += QString("Chance Card: %1\n").arg(QString::fromStdString(chance->getChanceText()));
        if(chance->getChanceText() == "Get out of jail card"){
            text += QString("Players who already have this card will not receive another one\n");
        }
    }else if (type == "Start") {
        text += QString("Start square! - Finish a round to receive 200$\n");
    }else if (type == "Tax") {
        Tax* tax = static_cast<Tax*>(currentSquare);
        text += QString("%1 - Pay: %2 $ \n")
                    .arg(QString::fromStdString(tax->getName()))
                    .arg(tax->getTaxAmount());
    }else if (type == "FreeParking"){
        //Nothing new to be printed
    }else if (type == "Jail") {
        //Nothing new to be printed
    }else if (type == "Tax") {
        text += QString("Name: %1\n").arg(QString::fromStdString(currentSquare->getName()));
    }
    else if (type == "GoToJail") {
        text += QString("Player is going to Jail!$\n");
    }



    squareInfoTextEdit->setPlainText(text);
}



QPoint MainWindow::getSquarePosition(int index) {
    const auto& squares = game->getSquares();

    if (index >= 0 && index < static_cast<int>(squares.size())) {
        Square* square = squares[index];
        return QPoint(square->getX(), square->getY());
    }

    return QPoint(-1, -1);
}
