#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Welcome)
{
    ui->setupUi(this);
    qDebug() << "Welcome widget created";
}

Welcome::~Welcome()
{
    delete ui;
    qDebug() << "Welcome widget deleted";
}

void Welcome::setStart()
{
    ui->message->setCurrentIndex(0);
}

void Welcome::setReadCard()
{
    ui->message->setCurrentIndex(1);
}

void Welcome::setCardReaderError()
{
    ui->message->setCurrentIndex(2);
}

void Welcome::on_pbstart_clicked()
{
    setReadCard();
    emit start();
}

void Welcome::on_pbok_clicked()
{
    setStart();
}
