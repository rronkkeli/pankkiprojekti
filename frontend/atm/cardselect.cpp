#include "cardselect.h"
#include "ui_cardselect.h"

CardSelect::CardSelect(QWidget *parent, LoginDLL *l)
    : QWidget(parent)
    , ui(new Ui::CardSelect)
{
    ui->setupUi(this);
    login = l;

    connect(
        login,
        SIGNAL(cardInfo(QJsonArray)),
        this,
        SLOT(accountSelect(QJsonArray))
    );

    login->getAccountInformation();
    qDebug() << "CardSelect widget created";
}

CardSelect::~CardSelect()
{
    delete ui;
    qDebug() << "CardSelect widget deleted";
}

void CardSelect::accountSelect(QJsonArray accounts)
{
    qsizetype len = accounts.size();
    if (len == 1) {
        emit selectedAccount(accounts.at(0).toObject());
        return;
    } else {
        qDebug() << "Double card detected. Splitting..";

        for (qsizetype i = 0; i < len; i++) {
            QJsonObject account = accounts.at(i).toObject();
            QString credit = account["credit"].toString();

            if (credit == "" || credit == "0.00" || credit == "0") {
                debit = account;
                qDebug() << "Debit set to: " << debit;
            } else {
                this->credit = account;
                qDebug() << "Credit set to: " << this->credit;
            }
        }

    }
}

void CardSelect::on_cardDebit_clicked()
{
    qDebug() << "Debit card was selected";
    emit selectedAccount(debit);
}


void CardSelect::on_cardCredit_clicked()
{
    qDebug() << "Credit card was selected";
    emit selectedAccount(credit);
}
