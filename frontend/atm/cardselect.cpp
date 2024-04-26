#include "cardselect.h"
#include "ui_cardselect.h"

CardSelect::CardSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardSelect)
{
    ui->setupUi(this);

    connect(
        ui->cardDebit,
        SIGNAL(clicked()),
        this,
        SLOT(accountSelect())
    );

    connect(
        ui->cardCredit,
        SIGNAL(clicked()),
        this,
        SLOT(accountSelect())
    );

    zeroize();

    qDebug() << "CardSelect widget created";
}

CardSelect::~CardSelect()
{
    delete ui;
    qDebug() << "CardSelect widget deleted";
}

void CardSelect::zeroize()
{
    type = Unset;
}

void CardSelect::accountSelect()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString choice = button->objectName();

    if (choice == "cardDebit") {
        type = Debit;
    } else if (choice == "cardCredit") {
        type = Credit;
    } else {
        zeroize();
    }

    emit selectedAccount(type);
}
