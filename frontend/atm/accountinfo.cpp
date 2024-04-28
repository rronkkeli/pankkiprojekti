#include "accountinfo.h"
#include "ui_accountinfo.h"

AccountInfo::AccountInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountInfo)
{
    ui->setupUi(this);

    qDebug() << "AccountInfo widget created";
}

AccountInfo::~AccountInfo()
{
    delete ui;
    qDebug() << "AccountInfo widget deleted";
}

void AccountInfo::getWithdrawalsInfo(QJsonArray wi)
{
    qDebug() << "Parsing withdrawals in widget. Got data: " << QJsonDocument(wi);

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

    withdrawals = data;
    ui->withdrawals->setText(data);
    qDebug() << "Withdrawal window was updated";
    refreshUI();
}

void AccountInfo::withdrawError(QString s)
{
    ui->withdrawals->setText(s);
}

void AccountInfo::handleCustomerInfo(QJsonArray array)
{
    QJsonObject c = array.at(0).toObject();
    QString fn = c["fname"].toString();
    QString ln = c["lname"].toString();

    customer = fn + " " + ln;
    ui->tervetuloteksti->setText("TERVETULOA "+customer+"\n\r 🐱‍👤🤳");
    refreshUI();
}

void AccountInfo::updateBalance(QString b)
{
    balance = b;
    ui->accountBalance->setText(balance);
    qDebug() << "Account balance updated.\n\r";
}

QString AccountInfo::editTimestamp(QString timestamp)
{
    QDateTime time = QDateTime::fromString(timestamp, Qt::ISODateWithMs);
    time = time.addSecs(3600);
    QString editedTime = time.toString("hh.mm dd.MM.yyyy");
    return editedTime;
}

void AccountInfo::setInfo(QJsonObject a, QString c, QString t)
{
    account = QString::number(a["idaccount"].toInt());
    balance = a["balance"].toString();
    credit = a["credit"].toString();
    type = t;
    card = c;
}

void AccountInfo::zeroize()
{
    type = account = balance = credit = card = customer = withdrawals = "";
    refreshUI();
}

void AccountInfo::refreshUI()
{
    ui->accountNumber->setText(account);
    ui->accountBalance->setText(balance);
    ui->accountType->setText(type);
    ui->accountOwner->setText(customer);
    ui->withdrawals->setText(withdrawals);
    ui->cardNumber->setText(card);
}

void AccountInfo::on_logout_clicked()
{
    emit logout();
}


void AccountInfo::on_withdraw_clicked()
{
    emit withdrawSignal();
}
