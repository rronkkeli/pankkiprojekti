#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QWidget>
#include "logindll.h"

namespace Ui {
class Withdraw;
}

class Withdraw : public QWidget
{
    Q_OBJECT

public:
    explicit Withdraw(QWidget *parent = nullptr, QString accountNumber = NULL, LoginDLL * login = nullptr);
    ~Withdraw();

private:
    Ui::Withdraw *ui;
    void sendWithdrawal();
    QString account;
    LoginDLL * login;
    QString withdrawal = "0";
    void add(QString);

signals:
    void returnToAccountInfo();


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
