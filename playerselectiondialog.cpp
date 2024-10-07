#include "PlayerSelectionDialog.h"
#include "qscreen.h"
#include "ui_PlayerSelectionDialog.h"

PlayerSelectionDialog::PlayerSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerSelectionDialog) {
    ui->setupUi(this);

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = ((screenGeometry.height() - height()) / 2) - 200;
    move(x, y);

    for (int i = 2; i <= 8; ++i) {
        ui->playerCountComboBox->addItem(QString::number(i));
    }

    connect(ui->okButton, &QPushButton::clicked, this, &PlayerSelectionDialog::onOkButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &PlayerSelectionDialog::onCancelButtonClicked);
}

PlayerSelectionDialog::~PlayerSelectionDialog() {
    delete ui;
}

int PlayerSelectionDialog::getNumberOfPlayers() const {
    return ui->playerCountComboBox->currentText().toInt();
}

void PlayerSelectionDialog::onOkButtonClicked() {
    accept();
}

void PlayerSelectionDialog::onCancelButtonClicked() {
    reject();
}
