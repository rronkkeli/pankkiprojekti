#include "mw1.h"
#include "mw2.h"
#include "ui_mw1.h"
#include "ui_mw2.h"
#include <QMessageBox>
#include <QString>


mw2::mw2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mw2)
    , card_ins(false) //initialization of card_ins
{
    ui->setupUi(this);
}

mw2::~mw2()
{
    delete ui;
}






