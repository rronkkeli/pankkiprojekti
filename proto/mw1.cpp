#include "mw1.h"
#include "mw2.h"
#include "ui_mw1.h"
#include "ui_mw2.h"
#include <QMessageBox>
#include <QString>


QString myString = "00000000"; //declaration of myString or "rfid", remove when merging with rfid module

mw1::mw1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mw1)
    , card_ins(false) //initialization of card_ins
{
    ui->setupUi(this);
}

mw1::~mw1()
{
    delete ui;
}
//cardDataReady() signaalin luku
void mw1::on_pb_ins_card_clicked()
{
    card_ins = true;
}


void mw1::on_pb_card_clicked()
{
    myString = "0000000001";
    QMessageBox::information(this,"Card","Id is now: " + myString);
}


void mw1::on_pb_login_clicked()
{
//    QString username = ui->le_username->text();

    if(card_ins && myString == "0000000001"){
        QMessageBox::information(this, "Login", "Welcome Administrator!");
        this->hide();

        //2nd UI
        mw2 *UI2 = new mw2();
        UI2->show();
    }
    else {
        QMessageBox::warning(this,"Login", "Error reading card or PIN");
    }
}





