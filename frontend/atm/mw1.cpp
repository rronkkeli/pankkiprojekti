#include "mw1.h"
#include "ui_mw1.h"
#include "dialog.h"
#include <QMessageBox>
#include <QString>

mw1::mw1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mw1)
    , card_ins(false) //initialization of card_ins
{
    ui->setupUi(this);

    // welcome = new Welcome(this);
    widget = new Welcome(this);

    cardReader = new RFID(this);
    pinUI = new PinUI(this);
    login = new LoginDLL(this);

    connect(
        cardReader,
        SIGNAL(cardDataReady()),
        this,
        SLOT(fetch_card_data())
    );

    connect(
        pinUI,
        SIGNAL(sendPinNumber(QString)),
        this,
        SLOT(set_pin(QString))
    );

    connect(
        login,
        SIGNAL(loginStatus(QString)),
        this,
        SLOT(setLoginStatus(QString))
    );

    connect(
        widget,
        SIGNAL(clicked()),
        this,
        SLOT(change())
    );
}

mw1::~mw1()
{
    delete ui;
    delete cardReader;
    delete pinUI;
    delete login;
    // delete info;
    // delete welcome;
    delete widget;
}

void mw1::fetch_card_data()
{
    cardNumber = cardReader->getCardData();
    // ui->cardNumber->setText(cardNumber);
    pinUI->show();
}

void mw1::set_pin(QString p)
{
    pin = p;
    pinUI->hide();
    login->login(cardNumber, pin);
}

void mw1::setLoginStatus(QString s)
{
    loginStatus = s;
    qDebug() << "Login status was set to: " << s;

    if (loginStatus == "success") {
        setWidget(2);
    }
}

void mw1::logout()
{
    pin = "";
    cardNumber = "";
    qDebug() << "Logged out or at least zeroed variables";
}

void mw1::setWidget(int type)
{
    switch (type) {
    case 1:
        delete widget;
        widget = new Welcome(this);
        widget->show();
        break;
    case 2:
        delete widget;
        widget = new AccountInfo(this);
        widget->show();
        break;
    default:
        break;
    }
}
