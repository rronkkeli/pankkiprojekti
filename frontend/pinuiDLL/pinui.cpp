#include "pinui.h"
#include "ui_pinui.h"

PinUI::PinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinUI)
{
    ui->setupUi(this);
}

PinUI::~PinUI()
{
    delete ui;
    qDebug() << "DLL Destroyed";
}

void PinUI::on_btnPin0_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin1_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin2_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin3_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin4_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin5_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin6_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin7_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin8_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPin9_clicked()
{
    pinNumberClickHandler();
}

void PinUI::on_btnPinClear_clicked()
{
    qDebug() << "Clicked CLEAR";

    pinNumber.clear();
    text.clear();

    qDebug() << "Pin number: " << pinNumber;
    qDebug() << "Line edit cleared: " << text << Qt::endl;

    ui->pinLineEdit->setText(text);
}

void PinUI::on_btnPinEnter_clicked()
{
    qDebug() << "Clicked ENTER";
    emit sendPinNumber(pinNumber);
    pinNumber = "";
    text = "";
    ui->pinLineEdit->clear();
}

void PinUI::pinNumberClickHandler()
{
    QPushButton * button = qobject_cast <QPushButton*> (sender());
    QString buttonName = button->objectName();
    qDebug() << "Clicked: " << buttonName;

    pinNumber = pinNumber + buttonName.last(1);
    text = text + "*";

    qDebug() << "Pin number: " << pinNumber;
    qDebug() << "Text in line edit: " << text << Qt::endl;

    ui->pinLineEdit->setText(text);
}

