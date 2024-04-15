#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include "customertests.h"

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr);
    ~AccountInfo();

private:
    Ui::AccountInfo *ui;
    CustomerTests *libCustomer;
    QString account;
    QString type;
    QString balance;
    QStringList withdrawals;

public slots:
    void getAccountInfo(QString, QString);
};

#endif // ACCOUNTINFO_H
