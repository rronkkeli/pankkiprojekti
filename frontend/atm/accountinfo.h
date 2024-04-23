#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "logindll.h"
#include "withdraw.h"

#include <QDateTime>

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr, LoginDLL *login = nullptr, QString card = "-", QJsonObject account = QJsonObject());
    ~AccountInfo();
    QString editTimestamp(QString);

private:
    Ui::AccountInfo *ui;
    QString account;
    QString type;
    QString balance;
    LoginDLL *login;
    QJsonArray withdrawalsInfo;


public slots:
    void getWithdrawalsInfo(QJsonArray);
    void getNostoInfo(QString);
    void getAccountRefresh(QJsonArray);

private slots:
    void on_logout_clicked();
    void on_withdraw_clicked();

signals:
    void logout();
    void withdrawSignal();
    void accountNumberSignal(QString);
};

#endif // ACCOUNTINFO_H
