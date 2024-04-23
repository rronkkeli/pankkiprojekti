#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "withdraw.h"

#include <QDateTime>

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr);
    ~AccountInfo();
    QString editTimestamp(QString);
    void setInfo(QJsonObject, QString, QString);
    void zeroize();
    void refreshUI();

private:
    Ui::AccountInfo *ui;
    QString card, account, type, balance, credit, customer, withdrawals;
    QJsonArray withdrawalsInfo;

public slots:
    void getWithdrawalsInfo(QJsonArray);
    void withdrawError(QString);

private slots:
    void on_logout_clicked();
    void on_withdraw_clicked();

signals:
    void logout();
    void withdrawSignal();
    void accountNumberSignal(QString);
};

#endif // ACCOUNTINFO_H
