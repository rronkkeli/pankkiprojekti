#include "withdraw.h"
#include "ui_withdraw.h"

Withdraw::Withdraw(QWidget *parent, QString accountNumber, LoginDLL * l) :
    QWidget(parent),
    ui(new Ui::Withdraw)
{
    ui->setupUi(this);
    account = accountNumber;
    qDebug() << "Account number in withdrawal constructor: " + account;
    qDebug() << "Withdraw widget created";
    login = l;
}

Withdraw::~Withdraw()
{
    delete ui;
}

void Withdraw::sendWithdrawal()
{
    login->nostotapahtuma(account, withdrawal);
}

void Withdraw::add(QString x)
{
    int y = x.toInt();
    int z = withdrawal.toInt();
    withdrawal = QString::number(y + z);
    ui->amountLineEdit->setText(withdrawal);

}

void Withdraw::on_withdrawalButton10_clicked()
{
    add("10");
}


void Withdraw::on_withdrawalButton20_clicked()
{
    add("20");
}


void Withdraw::on_withdrawalButton50_clicked()
{
    add("50");
}


void Withdraw::on_withdrawalButton100_clicked()
{
    add("100");
}


void Withdraw::on_withdrawalButton200_clicked()
{
    add("200");
}


void Withdraw::on_withdrawalButton500_clicked()
{
    add("500");
}


void Withdraw::on_pushButton_clicked()
{

    if (withdrawal.isEmpty() || withdrawal != "0"){
        sendWithdrawal();

        withdrawal = "0";

        emit returnToAccountInfo();

    }

    else{
        ui->amountLineEdit->setText("Syöttämäsi arvo ei voi olla 0!");
    }

}


void Withdraw::on_pushButtonGoBack_clicked()
{
    withdrawal = "0";
    emit returnToAccountInfo();
}


void Withdraw::on_pushButtonClear_clicked()
{
    withdrawal = "0";
    ui->amountLineEdit->setText(withdrawal);
}
