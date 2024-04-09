#ifndef CUSTOMERTESTS_H
#define CUSTOMERTESTS_H
#include <QDebug>
#include <QObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include "customerTests_global.h"

class CUSTOMERTESTS_EXPORT CustomerTests : public QObject
{
    Q_OBJECT
public:
    CustomerTests(QObject * parent);
    ~CustomerTests();

    void getCustomerInfo();
    void getWithdrawalsInfo();
    //void getTilitjaKortit();

    void addCustomer();

private:
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;

private slots:
    void getCustomerSlot (QNetworkReply *reply);
    void getWithdrawalsSlot (QNetworkReply *reply);
    //void getTilitjaKortitSlot (QNetworkReply *reply);

    void addCustomerSlot (QNetworkReply *reply);

signals:
    void customerInfo(QJsonArray);
    void withrawalsInfo(QJsonArray);
    //void tilitjakortitInfo(QJsonArray);

};

#endif // CUSTOMERTESTS_H
