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

    void getCardInformation();

    void getAccountInformation();

    void logout();

    void setCardNum(const QString &newCardNum);

    void setWebToken(const QByteArray &newWebToken);

    void setUserId(const QString &newUserId);

    void setAccountId(const QString &newAccountId);

    void getCustomerInfo();

    void getWithdrawalsInfo();

    void nostotapahtuma(QString tilin_numero,QString nostot);

    void getAccountRefresh();

    // Enums make it easy to handle different outcomes
    enum LoginStatus {
        InvalidCredentials,
        ConnectionError,
        Ok,
    };

private:
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *cardInfoManager;
    QNetworkAccessManager *accountInfoManager;
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QString socket;
    QString cardNum;
    QByteArray webToken;
    QString userId;
    QString accountId;

private slots:
    void loginSlot(QNetworkReply *reply);
    void cardInfoSlot(QNetworkReply *reply);
    void accountInfoSlot(QNetworkReply *reply);
    void getCustomerSlot(QNetworkReply *reply);
    void getWithdrawalsSlot(QNetworkReply *reply);

    void getNostotapahtumaSlot(QNetworkReply *reply);
    void getAccountRefreshSlot(QNetworkReply *reply);

signals:
    void loginStatus(LoginStatus);
    void customerInfo(QJsonArray);
    void withdrawalsInfo(QJsonArray);
    void accountInfo(QJsonArray);
    void nostotapahtumaInfo(QString);
    void cardInfo(QJsonArray);
    void withdrawalDone();
    void refreshDone();
    void accountDone(QJsonArray);
};

#endif // LOGINDLL_H
