#ifndef ADDSQUAREWINDOW_H
#define ADDSQUAREWINDOW_H

#include <QDialog>

namespace Ui {
class AddSquareWindow;
}

class MainWindow;

class AddSquareWindow : public QDialog {
    Q_OBJECT

public:
    explicit AddSquareWindow(MainWindow *parent = nullptr);
    ~AddSquareWindow();
    QString getSquareType() const;
    QString getSquareName() const;
    int getSelectedLine() const;

private slots:
    void onApplyButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::AddSquareWindow *ui;
    MainWindow *mainWindow;
};

#endif
