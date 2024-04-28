#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QWidget>
#include <QTimer>
#include "logindll.h"

namespace Ui {
class Withdraw;
}

class Withdraw : public QWidget
{
    Q_OBJECT

public:
    explicit Withdraw(QWidget *parent = nullptr);
    ~Withdraw();
    QTimer *timeout;

private:
    Ui::Withdraw *ui;
    QString withdrawal = "0";
    void add(QString);

signals:
    void sendWithdrawal(QString);

private slots:
    void on_withdrawalButton10_clicked();
    void on_withdrawalButton20_clicked();
    void on_withdrawalButton50_clicked();
    void on_withdrawalButton100_clicked();
    void on_withdrawalButton200_clicked();
    void on_withdrawalButton500_clicked();
    void on_pushButton_clicked();
    void on_pushButtonGoBack_clicked();
    void on_pushButtonClear_clicked();
};

#endif // WITHDRAW_H
