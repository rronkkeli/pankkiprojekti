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
        SIGNAL(loginStatus(LoginDLL::LoginStatus)),
        this,
        SLOT(setLoginStatus(LoginDLL::LoginStatus))
    );

}

mw1::~mw1()
{
    delete ui;
    delete cardReader;
    delete pinUI;
    delete login;
    delete widget;
}

void mw1::fetch_card_data()
{
    cardNumber = cardReader->getCardData();
    pinUI->show();
}

void mw1::set_pin(QString p)
{
    pin = p;
    pinUI->hide();
    login->login(cardNumber, pin);
}

void mw1::setLoginStatus(LoginDLL::LoginStatus s)
{
    loginStatus = s;
    qDebug() << "Login status was set to: " << s;

    switch (loginStatus) {
        case LoginDLL::LoginStatus::Ok:
            setWidget(SelectWidget::WidgetInfo);
            break;
        case LoginDLL::LoginStatus::InvalidCredentials:
            qDebug() << "Invalid credentials";
            delete pinUI;
            pinUI = new PinUI(this);
            pinUI->show();
            break;
        case LoginDLL::LoginStatus::ConnectionError:
            qDebug() << "Connection error while trying to log in";
            delete pinUI;
            pinUI = new PinUI(this);
            break;
    }

}

void mw1::logout()
{
    pin = "";
    cardNumber = "";
    qDebug() << "Logged out";

    setWidget(SelectWidget::WidgetWelcome);
}

void mw1::setWidget(SelectWidget type)
{
    switch (type) {
    case WidgetWelcome:
        delete widget;
        widget = new Welcome(this);
        widget->show();
        break;
    case WidgetInfo:
        delete widget;
        widget = new AccountInfo(this, login);
        widget->show();
        break;
    default:
        break;
    }
}
