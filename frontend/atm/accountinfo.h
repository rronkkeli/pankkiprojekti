#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "logindll.h"

#include <QDateTime>

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr, LoginDLL *login = nullptr, QString card = "-");
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
    void getAccountInfo(QJsonArray);
private slots:
    void on_logout_clicked();

signals:
    void logout();
};

#endif // ACCOUNTINFO_H
