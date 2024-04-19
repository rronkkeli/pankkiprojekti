#include "logindll.h"

LoginDLL::LoginDLL(QObject * parent):QObject(parent) {

    QString path = "socket";
    QFile socketfile(path);

    if (!socketfile.open(QFile::ReadOnly)) {
        qDebug() << "Opening socket file failed";
        socket = "http://localhost:3000";
    } else {
        socket = QLatin1String(socketfile.readAll());
    }

    qDebug() << "LoginDLL created";
}

LoginDLL::~LoginDLL()
{
    qDebug() << "LoginDLL deleted";
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
    QString site_url = socket + "/login";
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
    QString site_url = socket + "/card/" + cardNum;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer " + webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    cardInfoManager = new QNetworkAccessManager(this);
    connect(cardInfoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cardInfoSlot(QNetworkReply*)));
    reply = cardInfoManager->get(request);
}

void LoginDLL::getAccountInformation()
{
    qDebug() << "Got request for account information..";
    QString site_url = socket + "/card/accountDetails/" + cardNum;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken = "Bearer " + webToken;
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
    qDebug() << "Card number in logindll was set to: " << cardNum;
}

void LoginDLL::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void LoginDLL::setUserId(const QString &newUserId)
{
    userId = newUserId;
    qDebug()<<"User id " + userId + " was set in logindll";
}

void LoginDLL::setAccountId(const QString &newAccountId)
{
    accountId = newAccountId;
    qDebug()<<"Account id: " + accountId + "set By DLL";
}

void LoginDLL::cardInfoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() << "Card info: " << QString(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString card;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        card+=json_obj["idcard"].toString()+","+QString::number(json_obj["idcustomer"].toInt());
        setUserId(QString::number(json_obj["idcustomer"].toInt()));
        qDebug() << "UserId was set to " << userId << " by cardInfo";
    }

    reply->deleteLater();
    cardInfoManager->deleteLater();
}

void LoginDLL::accountInfoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    qDebug() << "Account info: " << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    qDebug() << "Account info length: " << json_array.size();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        setAccountId(QString::number(json_obj["idaccount"].toInt()));
    }

    emit cardInfo(json_array);
    reply->deleteLater();
    accountInfoManager->deleteLater();
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
        qDebug() << "Apparently login succeeded";
        status = LoginStatus::Ok;
        setWebToken(response_data);
        getCardInformation();
        qDebug() << "Logged in by logindll";
    } else {
        //Wrong card num or pin
        status = LoginStatus::InvalidCredentials;
        setCardNum(NULL);
    }
    emit loginStatus(status);

    reply->deleteLater();
    loginManager->deleteLater();
}

//GET CUSTOMER
void LoginDLL::getCustomerInfo()
{
    QString site_url = socket + "/customer";
    site_url.append("/" + userId);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(getCustomerSlot(QNetworkReply*)));
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
    QString site_url = socket + "/withdrawal";
    site_url.append("/" + accountId);
    qDebug() << "userId in getWithdrawalsInfo() was " << accountId;
    qDebug() << "Trying to access url " << site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(getWithdrawalsSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//GET WITHRAWAL SLOT
void LoginDLL::getWithdrawalsSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray accountinfo = json_doc.array();

    reply->deleteLater();
    getManager->deleteLater();
    emit withdrawalsInfo(accountinfo);
}

//GET TILIT JA KORTIT
void LoginDLL::getTilitjaKortitInfo()
{
    qDebug() << "Current userId is: " << userId << "(On row 216, logindll.cpp)";
    QString site_url = socket + "/tilitjakortit";
    site_url.append("/" + userId);

    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(getTilitjaKortitSlot(QNetworkReply*)));
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

    QString site_url= socket + "/nostotapahtuma";
    site_url.append("/" + userId);
    site_url.append("/" + tilin_numero);
    site_url.append("/" + nostot);

    qDebug() << site_url;

    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(getNostotapahtumaSlot(QNetworkReply*)));
    reply = getManager->get(request);
}


//NOSTOTAPAHTUMA SLOT
void LoginDLL::getNostotapahtumaSlot(QNetworkReply *reply)
{

    QByteArray responseData = reply->readAll();
    qDebug() << "DATA withdraw: " << responseData;

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
                    reply->deleteLater();
                    getManager->deleteLater();
                    return;
                }
            }
        }
    }
    emit withdrawalDone();
    reply->deleteLater();
    getManager->deleteLater();
}
