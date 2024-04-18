#include "mw1.h"
#include "ui_mw1.h"
#include "dialog.h"
#include <QMessageBox>
#include <QString>

mw1::mw1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mw1)
{
    ui->setupUi(this);
    setWidget(SelectWidget::WidgetWelcome);
    initialization = false;

    cardReader = new RFID(this);
    pinUI = new PinUI(this);

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
        SLOT(set_pin(QString)),
        Qt::UniqueConnection
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
            setWidget(SelectWidget::WidgetCardSelect);
            break;

        case LoginDLL::LoginStatus::InvalidCredentials:
            qDebug() << "Invalid credentials";
            delete pinUI;
            pinUI = new PinUI(this);

            connect(
                pinUI,
                SIGNAL(sendPinNumber(QString)),
                this,
                SLOT(set_pin(QString)),
                Qt::UniqueConnection
            );

            pinUI->show();
            break;

        case LoginDLL::LoginStatus::ConnectionError:
            qDebug() << "Connection error while trying to log in";
            delete pinUI;
            pinUI = new PinUI(this);

            connect(
                pinUI,
                SIGNAL(sendPinNumber(QString)),
                this,
                SLOT(set_pin(QString)),
                Qt::UniqueConnection
            );

            break;

        default:
            break;
    }

}

void mw1::logout()
{
    pin = "";
    cardNumber = "";
    login->logout();
    qDebug() << "Logged out";
    // disconnect(widget, SIGNAL(logout()), this, SLOT(logout()));
    setWidget(SelectWidget::WidgetWelcome);
}

void mw1::setAccount(QJsonObject a)
{
    account = a;
    setWidget(SelectWidget::WidgetInfo);
}

void mw1::setWidget(SelectWidget type)
{
    qDebug() << "Selecting widget..";
    switch (type) {
    case WidgetWelcome:
        qDebug() << "Welcome widget selected";
        if (!initialization) {
            qDebug() << "Deleting widget..";
            delete widget;
            delete login;
        }

        qDebug() << "Trying to create new LoginDLL..";
        login = new LoginDLL(this);

        connect(
            login,
            SIGNAL(loginStatus(LoginDLL::LoginStatus)),
            this,
            SLOT(setLoginStatus(LoginDLL::LoginStatus)),
            Qt::UniqueConnection
        );

        widget = new Welcome(this);
        widget->show();
        break;

    case WidgetInfo:
        qDebug() << "Info widget selected";
        delete widget;
        widget = new AccountInfo(this, login, cardNumber, account);

        connect(
            widget,
            SIGNAL(logout()),
            this,
            SLOT(logout()),
            Qt::UniqueConnection
        );

        widget->show();
        break;

    case WidgetCardSelect:
        qDebug() << "CardSelect widget selected";
        delete widget;
        widget = new CardSelect(this, login);

        connect(
            widget,
            SIGNAL(selectedAccount(QJsonObject)),
            this,
            SLOT(setAccount(QJsonObject)),
            Qt::UniqueConnection
        );

        widget->show();
        break;

    default:
        qDebug() << "No widget selected";
        break;
    }
}
