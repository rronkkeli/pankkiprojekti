#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include "logindll.h"

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr, LoginDLL *login = nullptr);
    ~AccountInfo();

private:
    Ui::AccountInfo *ui;
    QString account;
    QString type;
    QString balance;
    QStringList withdrawals;
    LoginDLL *login;

public slots:
    void getAccountInfo(QJsonArray);
};

#endif // ACCOUNTINFO_H
