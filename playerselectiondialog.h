#ifndef PLAYERSELECTIONDIALOG_HPP
#define PLAYERSELECTIONDIALOG_HPP

#include <QDialog>

namespace Ui {
class PlayerSelectionDialog;
}

class PlayerSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit PlayerSelectionDialog(QWidget *parent = nullptr);
    ~PlayerSelectionDialog();

    int getNumberOfPlayers() const;

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::PlayerSelectionDialog *ui;
};

#endif // PLAYERSELECTIONDIALOG_HPP
