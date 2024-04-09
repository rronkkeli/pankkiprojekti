#include "dialog.h"
#include "ui_dialog.h"
#include "mw1.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_LO_pb_clicked()
{
    this->hide();
}
