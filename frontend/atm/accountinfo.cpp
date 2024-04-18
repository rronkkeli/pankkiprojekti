#include "accountinfo.h"
#include "ui_accountinfo.h"

AccountInfo::AccountInfo(QWidget *parent, LoginDLL *l, QString card, QJsonObject account)
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

    ui->cardNumber->setText(card);

    QString credit = account["credit"].toString();
    QString accountNumber = QString::number(account["idaccount"].toInt());
    QString balance = account["balance"].toString();

    if (credit == "" || credit == "0" || credit == "0.00" || credit.isNull()) {
        ui->accountType->setText("Debit");
    } else {
        ui->accountType->setText("Credit (" + credit + ")");
    }

    login->setAccountId(accountNumber);
    login->getWithdrawalsInfo();

    ui->accountBalance->setText(balance);
    ui->accountNumber->setText(accountNumber);

    qDebug() << "AccountInfo widget created";
}

AccountInfo::~AccountInfo()
{
    delete ui;
    qDebug() << "AccountInfo widget deleted";
}

void AccountInfo::getWithdrawalsInfo(QJsonArray wi) {
    this->withdrawalsInfo = wi;
    qsizetype len = withdrawalsInfo.size();
    QString data = "Tunniste\tSumma\tNostoajankohta\r\n";

    for (qsizetype i = 0; i < len; i++) {
        QJsonObject row = withdrawalsInfo.at(i).toObject();

        QString id = QString::number(row["idwithdrawal"].toInt());
        QString amount = row["amount"].toString();
        QString time = row["timestamp"].toString();
        time = editTimestamp(time);
        data.append(id + "\t" + amount + "\t" + time + "\r\n");
    }

    ui->withdrawals->setText(data);
}

void AccountInfo::getAccountInfo(QJsonArray accountData)
{
    QJsonObject data = accountData.at(0).toObject();
    qsizetype len = accountData.size();

    QString id, balance, type;
    QString credit;

    id = QString::number(data["idaccount"].toInt());
    balance = data["balance"].toString();
    credit = data["credit"].toString();

    ui->accountBalance->setText(balance);
    ui->accountNumber->setText(id);

    qDebug() << "Credit: " << credit;

    if (credit == "") {
        type = QString("Debit");
    } else {
        if (credit != "0.00" || credit != "0") {
            type = QString("Credit (" + credit + ")");
        } else {
            type = QString("Debit");
        }
    }

    ui->accountType->setText(type);
}

QString AccountInfo::editTimestamp(QString timestamp)
{
    QDateTime time = QDateTime::fromString(timestamp, Qt::ISODateWithMs);
    QString editedTime = time.toString("hh.mm dd.MM.yyyy");
    return editedTime;
}

void AccountInfo::on_logout_clicked()
{
    emit logout();
}

