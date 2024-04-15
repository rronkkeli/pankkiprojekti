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

    connect(ptr_dll,SIGNAL(tilitjakortitInfo(QJsonArray)),
            this,SLOT(handlekortit(QJsonArray)));

    connect(ptr_dll,SIGNAL(nostotapahtumaInfo(QString)),
            this, SLOT(handlenostoInfo(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//Handle systeemit joissa laitetaan tiedot tekstiruutuun :)
void MainWindow::handleGottenInformation(QJsonArray customer)
{
    //Tässä kohdassa avataan tuo customer jsonarray :)
    ui->textCustomer->setText(customer);
}

void MainWindow::handlewithdrawals(QJsonArray tilitiedot)
{
    ui->textWithdrawals->setText(tilitiedot);
}

void MainWindow::handlekortit(QJsonArray)
{
    ui->textWithdrawals->setText(tilit);
    ui->textkortit->setText(kortit);
}

void MainWindow::handlenostoInfo(QString nosto)
{
    // Älä muokkaa tätä paitsi jos vaihat tuota kenttää mihin se teksti tulee
    ui->Virhetekstit->setText(nosto);
}

// Napinpainallus toiminnot
void MainWindow::on_btnkortitInfo_clicked()
{
    ptr_dll->getTilitjaKortitInfo();
}

void MainWindow::on_btnCustomerInfo_clicked()
{
    ptr_dll->getCustomerInfo();
}

void MainWindow::on_btnWithdrawalsInfo_clicked()
{
    ptr_dll->getWithdrawalsInfo();
}

void MainWindow::on_btnNostotapahtuma_clicked()
{
    QString tilin_numero;
    QString nosto;

    tilin_numero=ui->tilinumero->text();
    nosto=ui->summa->text();

    int myint = tilin_numero.toInt();
    float myfloat = nosto.toFloat();

    if(!tilin_numero.isNull() && !tilin_numero.isEmpty()&& !nosto.isNull() && !nosto.isEmpty() ){
        if(myint != NULL && myfloat != NULL){
            ptr_dll->nostotapahtuma(tilin_numero,nosto);
        }
        else{
            ui->textWithdrawals->setText("Syöttämäsi arvot eivät ole oikean tyyppisiä");
        }

    }
    else{
        ui->textWithdrawals->setText("Yritä syöttää arvot uudelleen");
    }



}

