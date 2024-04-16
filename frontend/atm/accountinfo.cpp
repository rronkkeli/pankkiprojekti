#include "accountinfo.h"
#include "ui_accountinfo.h"

AccountInfo::AccountInfo(QWidget *parent, LoginDLL *l, QString card)
    : QWidget(parent)
    , ui(new Ui::AccountInfo)
{
    ui->setupUi(this);
    this->login = l;

    connect(
        login,
        SIGNAL(withdrawalsInfo(QJsonArray)),
        this,
        SLOT(getWithdrawalsInfo(QJsonArray))
    );

    connect(
        login,
        SIGNAL(accountInfo(QJsonArray)),
        this,
        SLOT(getAccountInfo(QJsonArray))
    );

    ui->cardNumber->setText(card);
}

AccountInfo::~AccountInfo()
{
    delete ui;
    delete login;
}

void AccountInfo::getWithdrawalsInfo(QJsonArray wi) {
    this->withdrawalsInfo = wi.at(0).toArray();
    qsizetype len = withdrawalsInfo.size();
    QString data = "Tunniste\tSumma\tPäivämäärä\r\n";

    for (qsizetype i = 0; i < len; i++) {
        QJsonObject row = withdrawalsInfo.at(i).toObject();

        QString id = QString::number(row["idwithdrawal"].toInt());
        QString amount = row["amount"].toString();
        QString time = row["timestamp"].toString();

        data.append(id + "\t" + amount + "\t" + time + "\r\n");
    }

    ui->withdrawals->setText(data);
}

void AccountInfo::getAccountInfo(QJsonArray accountData)
{
    QJsonObject data = accountData.at(0).toObject();
    qsizetype len = accountData.size();

    QString id, balance, type;
    int credit;

    id = QString::number(data["idaccount"].toInt());
    balance = data["balance"].toString();
    credit = data["credit"].toInt();

    ui->accountBalance->setText(balance);
    ui->accountNumber->setText(id);

    if (&credit == nullptr) {
        type = QString("Debit");
    } else {
        if (credit > 0) {
            type = QString("Credit");
        } else {
            type = QString("Debit");
        }
    }

    ui->accountType->setText(type);
}
