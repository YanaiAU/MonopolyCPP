#include "addsquarewindow.h"
#include "qscreen.h"
#include "ui_addsquarewindow.h"
#include "mainwindow.hpp"

AddSquareWindow::AddSquareWindow(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::AddSquareWindow),
    mainWindow(parent) {
    ui->setupUi(this);

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    connect(ui->applyButton, &QPushButton::clicked, this, &AddSquareWindow::onApplyButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddSquareWindow::onCancelButtonClicked);
}

AddSquareWindow::~AddSquareWindow() {
    delete ui;
}

void AddSquareWindow::onApplyButtonClicked() {
    if (mainWindow) {
        int selectedOption = ui->lineComboBox->currentIndex();
        ui->lineComboBox->setItemData(selectedOption, QVariant(0), Qt::UserRole - 1);
    }
    accept();
}

void AddSquareWindow::onCancelButtonClicked() {
    reject();
}

QString AddSquareWindow::getSquareType() const {
    return ui->comboBox->currentText();
}

QString AddSquareWindow::getSquareName() const {
    return ui->inputTextBox->text();
}

int AddSquareWindow::getSelectedLine() const {
    int selectedOption = ui->lineComboBox->currentIndex();
    int index = selectedOption;
    ui->lineComboBox->setCurrentIndex(selectedOption + 1);
    return index;
}
