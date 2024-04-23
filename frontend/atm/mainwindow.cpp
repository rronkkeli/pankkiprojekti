#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    welcome = new Welcome(this);
    pinui = new PinUI(this);
    cardselect = new CardSelect(this);
    accountinfo = new AccountInfo(this);
    withdraw = new Withdraw(this);

    login = new LoginDLL(this);
    rfid = new RFID(this);

    ui->viewer->addWidget(welcome);
    ui->viewer->addWidget(pinui);
    ui->viewer->addWidget(cardselect);
    ui->viewer->addWidget(accountinfo);
    ui->viewer->addWidget(withdraw);

    ui->viewer->setCurrentWidget(welcome);

    connect(
        welcome,
        SIGNAL(start()),
        this,
        SLOT(start())
    );

    connect(
        rfid,
        SIGNAL(cardData(QString)),
        this,
        SLOT(handleData(QString))
    );

    connect(
        pinui,
        SIGNAL(sendPinNumber(QString)),
        this,
        SLOT(handleData(QString))
    );

    connect(
        login,
        SIGNAL(loginStatus(LoginDLL::LoginStatus)),
        this,
        SLOT(checkLoginStatus(LoginDLL::LoginStatus))
    );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete welcome;
    delete pinui;
    delete cardselect;
    delete accountinfo;
    delete withdraw;

    delete rfid;
    delete login;
}

void MainWindow::start()
{
    if (rfid->setReader()) {
        ui->viewer->setCurrentWidget(pinui);
    } else {
        welcome->setCardReaderError();
    }
}

void MainWindow::checkLoginStatus(LoginDLL::LoginStatus s)
{
    switch (s) {
        case LoginDLL::LoginStatus::Ok:
            // Check for double card
            break;

        case LoginDLL::LoginStatus::InvalidCredentials:
            // Show error message and try again or logout
            break;

        case LoginDLL::LoginStatus::ConnectionError:
            // Show connection error message
            break;

        default:
            break;
    }
}

void MainWindow::handleCardData(QString d)
{
    if (sender() == rfid) {
        card = d;
        ui->viewer->setCurrentWidget(pinui);
    } else if (sender() == pinui) {
        pin = d;
        login->login(card, pin);
    }
}
