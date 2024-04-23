#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    welcome = new Welcome(this);
    pinui = new PinUI(this);
    cardselect = new CardSelect(this);
    accountinfo = new AccountInfo(this);
    withdraw = new Withdraw(this);

    ui->viewer->addWidget(welcome);
    ui->viewer->addWidget(pinui);

    ui->viewer->setCurrentWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete welcome;
    delete pinui;
    delete cardselect;
    delete accountinfo;
    delete withdraw;

    delete rfid;
    delete login;
}
