#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonEXE_clicked()
{
    ptr_dll = new PinUI(this);
    ptr_dll->show();

    connect(ptr_dll,SIGNAL(sendPinNumber(QString)),
            this,SLOT(handlePinNumberDLLSignal(QString)));
}

void MainWindow::handlePinNumberDLLSignal(QString pinNum)
{
    ui->lineEditEXE->setText(pinNum);
}
