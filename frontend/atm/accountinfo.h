#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "logindll.h"

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr, LoginDLL *login = nullptr, QString card = "-");
    ~AccountInfo();

private:
    Ui::AccountInfo *ui;
    QString account;
    QString type;
    QString balance;
    LoginDLL *login;
    QJsonArray withdrawalsInfo;


public slots:
    void getWithdrawalsInfo(QJsonArray);
    void getAccountInfo(QJsonArray);
};

#endif // ACCOUNTINFO_H
