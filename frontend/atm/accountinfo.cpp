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
        SLOT(getWithdrawalsInfo(QJsonArray)),
        Qt::SingleShotConnection
    );

    ui->cardNumber->setText(card);

    QString credit = account["credit"].toString();
    this->account = QString::number(account["idaccount"].toInt());
    QString balance = account["balance"].toString();

    if (credit == "" || credit == "0" || credit == "0.00" || credit.isNull()) {
        ui->accountType->setText("Debit");
    } else {
        ui->accountType->setText("Credit (" + credit + ")");
    }

    login->setAccountId(this->account);

    ui->accountBalance->setText(balance);
    ui->accountNumber->setText(this->account);

    qDebug() << "AccountInfo widget created";
}

AccountInfo::~AccountInfo()
{
    delete ui;
    qDebug() << "AccountInfo widget deleted";
}

void AccountInfo::getWithdrawalsInfo(QJsonArray wi) {
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

    ui->withdrawals->setText(data);
    qDebug() << "Withdrawal window was updated";
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


void AccountInfo::on_withdraw_clicked()
{
    emit withdrawSignal();
}

