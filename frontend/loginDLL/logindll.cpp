#include "logindll.h"

LoginDLL::LoginDLL(QObject * parent):QObject(parent) {

}

LoginDLL::~LoginDLL()
{

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
    connect(loginManager, SIGNAL(finished (QNetworkReply*)),
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
    QString status;
    qDebug()<<response_data;
    //Show user what the response is and send info to main program for message boxes
    if(response_data =="-4078" || response_data.length() == 0) {
        //No database connection
        status = "Virhe tietokantayhteydessä";
        setCardNum(NULL);
        emit loginStatus(status);
    }
    else if(response_data != "false") {
        //Success
        status = "success";
        setWebToken(response_data);
        getCardInformation();
        getAccountInformation();
        emit loginStatus(status);
    } else {
        //Wrong card num or pin
        status = "Kortin numero tai pin ei täsmää.";
        setCardNum(NULL);
        emit loginStatus(status);
    }
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
void LoginDLL::getCustomerSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    //Tässä kohtaa signaali käsittelevään hommaan mainissa

    QString customer;

    customer="asiakas_numero | Etunimi | Sukunimi | puhelinnumero | syntymÃ¤aika | osoite \r\n";

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        customer+=QString::number(json_obj["idcustomer"].toInt())+"  |  ";
        customer+=json_obj["fname"].toString()+"  |  ";
        customer+=json_obj["lname"].toString()+"  |  ";
        customer+=json_obj["phone_number"].toString()+"  |  ";
        customer+=json_obj["birthdate"].toString()+"  |  ";
        customer+=json_obj["address"].toString()+"  |  ";
        customer+="\r\n";
    }
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
void LoginDLL::getWithdrawalsSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();


    QString tilitiedot;


    tilitiedot="Noston id  |  määrä  |  päiväys \r\n";

    QJsonArray tilitiedotArray = json_array.at(0).toArray();
    foreach (const QJsonValue &value, tilitiedotArray) {
        QJsonObject json_obj = value.toObject();

        tilitiedot+=QString::number(json_obj["idwithdrawal"].toInt())+"  |  ";
        tilitiedot+=QString::number(json_obj["idaccount"].toInt())+"  |  ";
        tilitiedot+=json_obj["amount"].toString()+"  |  ";
        tilitiedot+=json_obj["timestamp"].toString()+" \r\n";
    }

    emit withdrawalsInfo(tilitiedot);

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

    //Tässä kohtaa signaali käsittelevään hommaan mainissa
    QString tilit;
    QString kortit;

    // Alustetaan tilit- ja kortit-merkkijonot otsikoilla
    tilit = "Tilit_id | saldo | credit \n";
    kortit = "Yhdistetyn tilin id | kortin numero | pin \n";

    // Käsitellään tilit
    QJsonArray tilitArray = json_array.at(0).toArray();
    foreach (const QJsonValue &value, tilitArray) {
        QJsonObject json_obj = value.toObject();
        tilit += QString::number(json_obj["idaccount"].toInt()) + " | ";
        tilit += json_obj["balance"].toString() + " | ";
        tilit += json_obj["credit"].toString() + "\n";
    }

    // Käsitellään kortit
    QJsonArray kortitArray = json_array.at(1).toArray();
    foreach (const QJsonValue &value, kortitArray) {
        QJsonObject json_obj = value.toObject();
        kortit += QString::number(json_obj["idaccount"].toInt()) + " | ";
        kortit += json_obj["idcard"].toString() + " | ";
        kortit += json_obj["pin"].toString() + "\n";
    }

    emit tilitjakortitInfo(tilit,  kortit);
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
