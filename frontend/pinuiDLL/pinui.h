#ifndef PINUI_H
#define PINUI_H

#include <QDebug>
#include <QDialog>
#include <QTimer>
#include "pinuiDLL_global.h"

namespace Ui {
class PinUI;
}

class PINUIDLL_EXPORT PinUI : public QWidget
{
    Q_OBJECT

public:
    explicit PinUI(QWidget *parent = nullptr);
    ~PinUI();
    void setAlert(bool);
    QTimer *timeout;

signals:
    void sendPinNumber(QString);
    void pinCancel();

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
    void on_btnPinCancel_clicked();

private:
    Ui::PinUI *ui;
    QString pinNumber;
    QString text;
    void pinNumberClickHandler();
};

#endif // PINUI_H
