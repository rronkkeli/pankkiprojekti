#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ptr_dll = new CustomerTests(this);

    connect(ptr_dll,SIGNAL(customerInfo(QString)),
            this,SLOT(handleGottenInformation(QString)));

    connect(ptr_dll,SIGNAL(withdrawalsInfo(QString)),
            this,SLOT(handlewithdrawals(QString)));

    connect(ptr_dll,SIGNAL(tilitjakortitInfo(QString, QString)),
            this,SLOT(handlekortit(QString, QString)));

    connect(ptr_dll,SIGNAL(nostotapahtumaInfo(QString)),
            this, SLOT(handlenostoInfo(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//Handle systeemit joissa laitetaan tiedot tekstiruutuun :)
void MainWindow::handleGottenInformation(QString customer)
{
    ui->textCustomer->setText(customer);
}

void MainWindow::handlewithdrawals(QString tilitiedot)
{
    ui->textWithdrawals->setText(tilitiedot);
}

void MainWindow::handlekortit(QString tilit,QString kortit)
{
    ui->textWithdrawals->setText(tilit);
    ui->textkortit->setText(kortit);
}

void MainWindow::handlenostoInfo(QString nosto)
{
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

void MainWindow::on_btnPost_clicked()
{
    QString asiakas;
    asiakas=ui->asiakasruutu->text();
    ptr_dll->setAsiakas(asiakas);
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

