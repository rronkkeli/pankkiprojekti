#ifndef PINUI_H
#define PINUI_H

#include <QDebug>
#include <QDialog>
#include "pinuiDLL_global.h"

namespace Ui {
class PinUI;
}

class PINUIDLL_EXPORT PinUI : public QDialog
{
    Q_OBJECT

public:
    explicit PinUI(QWidget *parent = nullptr);
    ~PinUI();

signals:
    void sendPinNumber(QString);

private slots:
    void on_btnPin0_clicked();
    void on_btnPin1_clicked();
    void on_btnPin2_clicked();
    void on_btnPin3_clicked();
    void on_btnPin4_clicked();
    void on_btnPin5_clicked();
    void on_btnPin6_clicked();
    void on_btnPin7_clicked();
    void on_btnPin8_clicked();
    void on_btnPin9_clicked();
    void on_btnPinClear_clicked();
    void on_btnPinEnter_clicked();
    void on_btnPinBackspace_clicked();

private:
    Ui::PinUI *ui;
    QString pinNumber;
    QString text;
    void pinNumberClickHandler();
};

#endif // PINUI_H
