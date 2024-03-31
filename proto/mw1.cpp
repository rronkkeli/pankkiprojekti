#include "mw1.h"
#include "ui_mw1.h"
#include <QMessageBox>
#include <QString>


QString myString = "0000"; //declaration of myString or "rfid", remove when merging with rfid module

mw1::mw1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mw1)
{
    ui->setupUi(this);
}

mw1::~mw1()
{
    delete ui;
}

void mw1::on_pb_card_clicked()
{
    myString = "0001";
    QMessageBox::information(this,"Card","Id is now: " + myString);
}


void mw1::on_pb_login_clicked()
{
    QString username = ui->le_username->text();

    if(username == "admin" && myString == "0001"){
        QMessageBox::information(this, "Login", "Welcome Administrator!");
    }
    else {
        QMessageBox::warning(this,"Login", "Wrong username or Id");
    }
}

