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
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>


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

    //music
    QMediaPlayer * music;
    QAudioOutput * audioOutput;


    // Widgets
    Welcome *welcome;
    PinUI *pinui;
    CardSelect *cardselect;
    AccountInfo *accountinfo;
    Withdraw *withdraw;

    // Libraries
    RFID *rfid;
    LoginDLL *login;

    // Functions

    // Variables
    QString pin, cardNum, accountid;
    QJsonObject debit, credit;
    QTimer *logoutTimer, *startWidgetTimer;
    int tries = 0;

private slots:
    void start();
    void logout();
    void returnToStart();
    void handleData(QString);
    void handleAccounts(QJsonArray);
    void checkLoginStatus(LoginDLL::LoginStatus);
    void handleAccountSelect(CardSelect::AccountType);
    void handleWithdrawal(QString);
    void openWithdrawWidget();
    void refetchWithdrawals();
};

#endif // MAINWINDOW_H
