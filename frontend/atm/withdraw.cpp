#include "withdraw.h"
#include "ui_withdraw.h"

Withdraw::Withdraw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Withdraw)
{
    ui->setupUi(this);
    qDebug() << "Withdraw widget created";
}

Withdraw::~Withdraw()
{
    delete ui;
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
    if (withdrawal != "0") {
        emit sendWithdrawal(withdrawal);
        withdrawal = "0";
        ui->amountLineEdit->setText(withdrawal);

    } else {
        ui->amountLineEdit->setText("Syötä arvo!!");
    }
}


void Withdraw::on_pushButtonGoBack_clicked()
{
    withdrawal = "0";
    ui->amountLineEdit->setText(withdrawal);
    emit sendWithdrawal(withdrawal);
}


void Withdraw::on_pushButtonClear_clicked()
{
    withdrawal = "0";
    ui->amountLineEdit->setText(withdrawal);
}
