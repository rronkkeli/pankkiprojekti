#include "customertests.h"

CustomerTests:: CustomerTests(QObject * parent):QObject(parent) {
    qDebug()<<"DLL luotu";
}

CustomerTests::~CustomerTests()
{
    qDebug()<<"DLL tuhottu";
}


//GET CUSTOMER
void CustomerTests::getCustomerInfo()
{
    QString site_url="http://localhost:3000/customer";
    site_url.append("/" + getAsiakas());
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getCustomerSlot(QNetworkReply*)));
    reply = getManager->get(request);
}
//GET CUSTOMER SLOT
void CustomerTests::getCustomerSlot (QNetworkReply *reply)
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
void CustomerTests::getWithdrawalsInfo()
{
    QString site_url="http://localhost:3000/tilitiedot";
    site_url.append("/" + getAsiakas());
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getWithdrawalsSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//GET WITHRAWAL SLOT
void CustomerTests::getWithdrawalsSlot (QNetworkReply *reply)
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
void CustomerTests::getTilitjaKortitInfo()
{
    QString site_url="http://localhost:3000/tilitjakortit";
    site_url.append("/" + getAsiakas());

    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitjaKortitSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//GET TILIT JA KORTIT SLOT
void CustomerTests::getTilitjaKortitSlot(QNetworkReply *reply)
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
void CustomerTests::nostotapahtuma(QString tilin_numero,QString nostot)
{

    QString site_url="http://localhost:3000/nostotapahtuma";
    site_url.append("/" + getAsiakas());
    site_url.append("/" + tilin_numero);
    site_url.append("/" + nostot);



    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getNostotapahtumaSlot(QNetworkReply*)));
    reply = getManager->get(request);
}


//NOSTOTAPAHTUMA SLOT
void CustomerTests::getNostotapahtumaSlot (QNetworkReply *reply)
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
                    QByteArray data = QJsonDocument(firstObject).toJson();
                    emit nostotapahtumaInfo(data);
                    return;
                }
            }
        }

    }
    reply->deleteLater();
    getManager->deleteLater();
}

//asiakkaan numeron saanti get/set
QString CustomerTests::getAsiakas() const
{
    return asiakas;
}

void CustomerTests::setAsiakas(const QString &newAsiakas)
{
    asiakas = newAsiakas;
}


