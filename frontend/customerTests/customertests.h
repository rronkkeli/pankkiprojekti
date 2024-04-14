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
    void getTilitjaKortitInfo();
    void nostotapahtuma(QString tilin_numero,QString nostot);


    QString getAsiakas() const;
    void setAsiakas(const QString &newAsiakas);

private:
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QString asiakas;

private slots:
    void getCustomerSlot (QNetworkReply *reply);
    void getWithdrawalsSlot (QNetworkReply *reply);
    void getTilitjaKortitSlot (QNetworkReply *reply);

    void getNostotapahtumaSlot (QNetworkReply *reply);

signals:
    void customerInfo(QString);
    void withdrawalsInfo(QString withdrawal);
    void tilitjakortitInfo(QString tilit, QString kortit);
    void nostotapahtumaInfo(QString);

};

#endif // CUSTOMERTESTS_H
