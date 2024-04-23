#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "welcome.h"
#include "pinui.h"
#include "cardselect.h"
#include "accountinfo.h"
#include "withdraw.h"
#include "rfid.h"
#include "logindll.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Widgets
    Welcome *welcome;
    PinUI *pinui;
    CardSelect *cardselect;
    AccountInfo *accountinfo;
    Withdraw *withdraw;

    // Libraries
    RFID *rfid;
    LoginDLL *login;
};

#endif // MAINWINDOW_H
