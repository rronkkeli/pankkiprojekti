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

    connect(
        login,
        SIGNAL(cardInfo(QJsonArray)),
        this,
        SLOT(handleCard(QJsonArray))
    );

    connect(
        login,
        SIGNAL(withdrawalsInfo(QJsonArray)),
        accountinfo,
        SLOT(getWithdrawalsInfo(QJsonArray))
    );

    connect(
        login,
        SIGNAL(nostotapahtumaInfo(QString)),
        accountinfo,
        SLOT(withdrawError(QString))
    );

    connect(
        login,
        SIGNAL(withdrawalDone()),
        this,
        SLOT(refetchWithdrawals())
    );

    connect(
        cardselect,
        SIGNAL(selectedAccount(CardSelect::AccountType)),
        this,
        SLOT(handleAccountSelect(CardSelect::AccountType))
    );

    connect(
        accountinfo,
        SIGNAL(withdrawSignal()),
        this,
        SLOT(openWithdrawWidget())
    );

    connect(
        accountinfo,
        SIGNAL(logout()),
        this,
        SLOT(logout())
    );

    connect(
        withdraw,
        SIGNAL(sendWithdrawal(QString)),
        this,
        SLOT(handleWithdrawal(QString))
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

void MainWindow::handleCard(QJsonArray accounts)
{
    qDebug() << "Processing card information";
    QJsonObject account;

    qsizetype len = accounts.size();
    if (len == 1) {
        qDebug() << "Single account detected..";
        account = (accounts.at(0).toObject());

        QString creditamt = account["credit"].toString();
        QString type;

        accountid = QString::number(account["idaccount"].toInt());

        if (creditamt == "" || creditamt == "0.00" || creditamt == "0") {
            type = "Debit";
        } else {
            type = "Credit (" + account["credit"].toString() + ")";
        }

        accountinfo->setInfo(
            account,
            cardNum,
            type
        );

        ui->viewer->setCurrentWidget(accountinfo);
        login->getWithdrawalsInfo();
        return;

    } else {
        qDebug() << "Double card detected. Splitting..";

        for (qsizetype i = 0; i < len; i++) {
            account = accounts.at(i).toObject();
            QString creditamt = account["credit"].toString();

            if (creditamt == "" || creditamt == "0.00" || creditamt == "0") {
                debit = account;
                qDebug() << "Debit set to: " << debit;

            } else {
                credit = account;
                qDebug() << "Credit set to: " << credit;

            }
        }

        ui->viewer->setCurrentWidget(cardselect);

    }
}

void MainWindow::logout()
{
    login->logout();
    cardselect->zeroize();
    accountinfo->zeroize();
    debit = credit = QJsonObject();
    pin = cardNum = "";
    welcome->setStart();
    ui->viewer->setCurrentWidget(welcome);
}

void MainWindow::start()
{
    if (!rfid->setReader()) {
        welcome->setCardReaderError();
    }
}

void MainWindow::checkLoginStatus(LoginDLL::LoginStatus s)
{
    switch (s) {
        case LoginDLL::LoginStatus::Ok:
            login->getAccountInformation();
            break;

        case LoginDLL::LoginStatus::InvalidCredentials:
            if (tries < 3) {
                tries++;
                pinui->setAlert(true);
                ui->viewer->setCurrentWidget(pinui);

            } else {
                logout();
                pinui->setAlert(false);
                ui->viewer->setCurrentWidget(welcome);

            }
            break;

        case LoginDLL::LoginStatus::ConnectionError:
            // TODO: Show connection error message
            break;

        default:
            break;
    }
}

void MainWindow::handleAccountSelect(CardSelect::AccountType t)
{
    switch (t) {
    case CardSelect::AccountType::Debit:
        accountinfo->setInfo(debit, cardNum, "Debit");
        accountid = QString::number(debit["idaccount"].toInt());
        break;

    case CardSelect::AccountType::Credit:
        accountinfo->setInfo(credit, cardNum, "Credit (" + credit["credit"].toString() + ")");
        accountid = QString::number(credit["idaccount"].toInt());
        break;

    default:
        qDebug() << "Unexpected value as AccountType";
        break;
    }

    accountinfo->refreshUI();
    ui->viewer->setCurrentWidget(accountinfo);
    login->getWithdrawalsInfo();
}

void MainWindow::handleWithdrawal(QString withdrawal)
{
    if (withdrawal != "0") {
        qDebug() << "Withdrawal from account " + accountid + " with sum of " + withdrawal;
        login->nostotapahtuma(accountid, withdrawal);
    }

    ui->viewer->setCurrentWidget(accountinfo);
}

void MainWindow::openWithdrawWidget()
{
    ui->viewer->setCurrentWidget(withdraw);
}

void MainWindow::refetchWithdrawals()
{
    qDebug() << "Refetching withdrawals..";
    login->getWithdrawalsInfo();
}

void MainWindow::handleData(QString d)
{
    if (sender() == rfid) {
        cardNum = d;
        pinui->setAlert(false);
        tries = 0;
        ui->viewer->setCurrentWidget(pinui);
        rfid->closeReader();

    } else if (sender() == pinui) {
        pin = d;
        welcome->setLoggingIn();
        ui->viewer->setCurrentWidget(welcome);
        login->login(cardNum, pin);
    }
}
