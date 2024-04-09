#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ptr_dll = new CustomerTests(this);

    connect(ptr_dll,SIGNAL(customerInfo(QJsonArray)),
            this,SLOT(handleGottenInformation(QJsonArray)));

    connect(ptr_dll,SIGNAL(withdrawalsInfo(QJsonArray)),
            this,SLOT(handlewithdrawals(QJsonArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleGottenInformation(QJsonArray json_array)
{
    QString customer;

    customer="asiakas_numero | Etunimi | Sukunimi | puhelinnumero | syntymÃ¤aika | osoite \r\n";

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        customer+=QString::number(json_obj["idcustomer"].toInt())+"  |  ";

        customer+=json_obj["fname"].toString()+"  |  ";
        customer+=json_obj["lname"].toString()+"  |  ";
        customer+=json_obj["phone_number"].toString()+"  |  ";
        customer+=json_obj["birthdate"].toString()+"  |  ";
        customer+=json_obj["address"].toString()+"  |  ";
        customer+="\r\n";
    }

    ui->textCustomer->setText(customer);
}

void MainWindow::handlewithdrawals(QJsonArray json_array)
{

    QString withdrawal;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        withdrawal+=QString::number(json_obj["idwithdrawal"].toInt())+", "+json_obj["amount"].toString()+", "+json_obj["timestamp"].toString()+"\r";
        ui->textWithdrawals->setText(withdrawal);
    }


}



void MainWindow::on_btnCustomerInfo_clicked()
{
    //Kutsutaan DLL
    //DLL lähettää tietokannasta saadut tiedot customerInfo-signaalissa

    ptr_dll->getCustomerInfo();
}

void MainWindow::on_btnWithdrawalsInfo_clicked()
{
    ptr_dll->getWithdrawalsInfo();
}

void MainWindow::on_btnPost_clicked()
{
    ptr_dll->addCustomer();
}

