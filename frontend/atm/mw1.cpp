#include "mw1.h"
#include "ui_mw1.h"
#include "dialog.h"
#include <QMessageBox>
#include <QString>

mw1::mw1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mw1)
    , card_ins(false) //initialization of card_ins
{
    ui->setupUi(this);
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
        SLOT(set_pin(QString))
    );
}

mw1::~mw1()
{
    delete ui;
    delete cardReader;
    delete pinUI;
}

void mw1::fetch_card_data()
{
    cardNumber = cardReader->getCardData();
    ui->cardNumber->setText(cardNumber);
    pinUI->show();
}

void mw1::set_pin(QString p)
{
    pin = p;
    ui->pinNumber->setText(pin);
    pinUI->hide();
}

void mw1::on_pb_login_clicked()
{
//    QString username = ui->le_username->text();

    if(!cardNumber.isEmpty()){
        QMessageBox::information(this, "Login", "Welcome Administrator!");
        // Do some questionable shit here, like login.
        //modal for 2nd window
        Dialog secDialog;
        secDialog.setModal(true);
        secDialog.exec();
    }
    else {
        QMessageBox::warning(this,"Login", "Error reading card or PIN");
    }
}
