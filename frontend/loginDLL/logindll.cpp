#include "logindll.h"

LoginDLL::LoginDLL(QObject * parent):QObject(parent) {

}

LoginDLL::~LoginDLL()
{
    delete loginManager;
    delete cardInfoManager;
    delete accountInfoManager;
    delete getManager;
    delete postManager;
    delete reply;
}

void LoginDLL::login(QString cardId, QString cardPin)
{
    //Bring cardId to a variable
    setCardNum(cardId);
    //Json-object and inserting data to it
    QJsonObject jsonObj;
    jsonObj.insert("pin",cardPin);
    jsonObj.insert("idcard",cardId);

    //URL etc.
    QString site_url = "http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //Signals etc.
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request,QJsonDocument(jsonObj).toJson());
}

void LoginDLL::getCardInformation()
{
    QString site_url="http://localhost:3000/card/" + cardNum;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    cardInfoManager = new QNetworkAccessManager(this);

    connect(cardInfoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(cardInfoSlot(QNetworkReply*)));
    reply = cardInfoManager->get(request);
}

void LoginDLL::getAccountInformation()
{
    QString site_url="http://localhost:3000/card/accountDetails/" + cardNum;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    accountInfoManager = new QNetworkAccessManager(this);

    connect(accountInfoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(accountInfoSlot(QNetworkReply*)));
    reply = accountInfoManager->get(request);
}

void LoginDLL::logout()
{

    setWebToken(NULL);
    setAccountId(NULL);
    setCardNum(NULL);
    setUserId(NULL);
    //Suljetaan ikkuna pääsovelluksessa
}

void LoginDLL::setCardNum(const QString &newCardNum)
{
    cardNum = newCardNum;
    qDebug()<<cardNum;
}

void LoginDLL::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void LoginDLL::setUserId(const QString &newUserId)
{
    userId = newUserId;
    qDebug()<<"User id " + userId;
}

void LoginDLL::setAccountId(const QString &newAccountId)
{
    accountId = newAccountId;
    qDebug()<<"Account id: " + accountId;
}

void LoginDLL::cardInfoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString card;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        card+=json_obj["idcard"].toString()+","+QString::number(json_obj["idcustomer"].toInt());
        setUserId(QString::number(json_obj["idcustomer"].toInt()));
    }
}

void LoginDLL::accountInfoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        setAccountId(QString::number(json_obj["idaccount"].toInt()));
    }
}

void LoginDLL::loginSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    LoginStatus status;
    qDebug()<<response_data;
    //Show user what the response is and send info to main program for message boxes
    if(response_data =="-4078" || response_data.length() == 0) {
        //No database connection
        status = LoginStatus::ConnectionError;
        setCardNum(NULL);
    }
    else if(response_data != "false") {
        //Success
        status = LoginStatus::Ok;
        setWebToken(response_data);
        getCardInformation();
        getAccountInformation();
    } else {
        //Wrong card num or pin
        status = LoginStatus::InvalidCredentials;
        setCardNum(NULL);
    }
    emit loginStatus(status);
}

//GET CUSTOMER
void LoginDLL::getCustomerInfo()
{
    QString site_url="http://localhost:3000/customer";
    site_url.append("/" + userId);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getCustomerSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//GET CUSTOMER SLOT
void LoginDLL::getCustomerSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray customer = json_doc.array();

    emit customerInfo(customer);
    reply->deleteLater();
    getManager->deleteLater();
}

//GET WITHRAWAL
void LoginDLL::getWithdrawalsInfo()
{
    QString site_url="http://localhost:3000/tilitiedot";
    site_url.append("/" + userId);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getWithdrawalsSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//GET WITHRAWAL SLOT
void LoginDLL::getWithdrawalsSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray accountinfo = json_doc.array();

    emit withdrawalsInfo(accountinfo);
    reply->deleteLater();
    getManager->deleteLater();
}

//GET TILIT JA KORTIT
void LoginDLL::getTilitjaKortitInfo()
{
    QString site_url="http://localhost:3000/tilitjakortit";
    site_url.append("/" + userId);

    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitjaKortitSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//GET TILIT JA KORTIT SLOT
void LoginDLL::getTilitjaKortitSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    emit tilitjakortitInfo(json_array);
    qDebug()<<json_array;

    reply->deleteLater();
    getManager->deleteLater();
}


//NOSTOTAPAHTUMA
void LoginDLL::nostotapahtuma(QString tilin_numero,QString nostot)
{

    QString site_url="http://localhost:3000/nostotapahtuma";
    site_url.append("/" + userId);
    site_url.append("/" + tilin_numero);
    site_url.append("/" + nostot);



    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getNostotapahtumaSlot(QNetworkReply*)));
    reply = getManager->get(request);
}


//NOSTOTAPAHTUMA SLOT
void LoginDLL::getNostotapahtumaSlot (QNetworkReply *reply)
{

    QByteArray responseData = reply->readAll();
    qDebug() << "DATA : " << responseData;

    if (reply->error() == QNetworkReply::NoError) {
        QJsonParseError jsonError;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData, &jsonError);

        if (jsonError.error == QJsonParseError::NoError && jsonResponse.isArray()) {
            QJsonArray jsonArray = jsonResponse.array();
            if (!jsonArray.isEmpty() && jsonArray.at(0).isArray()) {
                QJsonArray firstArray = jsonArray.at(0).toArray();
                if (!firstArray.isEmpty() && firstArray.size() == 1 && firstArray.at(0).isObject()) {
                    QJsonObject firstObject = firstArray.at(0).toObject();
                    emit nostotapahtumaInfo(firstObject.keys()[0]);
                    return;
                }
            }
        }

    }
    reply->deleteLater();
    getManager->deleteLater();
}
