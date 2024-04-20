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
