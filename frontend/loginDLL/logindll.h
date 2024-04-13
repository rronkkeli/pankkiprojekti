#ifndef LOGINDLL_H
#define LOGINDLL_H

#include <QDebug>
#include <QObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include "loginDLL_global.h"

class LOGINDLL_EXPORT LoginDLL : public QObject
{
    Q_OBJECT
public:
    LoginDLL(QObject * parent);
    ~LoginDLL();
    void login(QString cardId, QString cardPin);

private:
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

private slots:
    void loginSlot(QNetworkReply *reply);

signals:
    void loginStatus(QString);
};

#endif // LOGINDLL_H
