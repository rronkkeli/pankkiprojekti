#include "customertests.h"

CustomerTests:: CustomerTests(QObject * parent):QObject(parent) {
    qDebug()<<"DLL luotu";
}

CustomerTests::~CustomerTests()
{
    qDebug()<<"DLL tuhottu";
}


//GET
void CustomerTests::getCustomerInfo()
{
    QString site_url="http://localhost:3000/customer/1";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getCustomerSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

//POST
void CustomerTests::addCustomer()
{
    //Tämän kohdan voi toteuttaa myös niin, että haetaan ikkunasta tiedot ja heitetään ne muuttujiin. Esimerkkinä kuitenkin koodissa muokkaukset
    QJsonObject jsonObj;
    jsonObj.insert("fname","Matti");
    jsonObj.insert("lname","Mainio");
    jsonObj.insert("phone_number","123456789");
    jsonObj.insert("birthdate","2000-10-10");
    jsonObj.insert("address","Testitie 13");

    QString site_url="http://localhost:3000/customer";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)),
            this, SLOT(addCustomerSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

//GET SLOT
void CustomerTests::getCustomerSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    //Tässä kohtaa signaali käsittelevään hommaan mainissa
    emit customerInfo(json_array);
    qDebug()<<json_array;

    // QString customer;
    // foreach (const QJsonValue &value, json_array) {
    //     QJsonObject json_obj = value.toObject();
    //     customer+=QString::number(json_obj["idcustomer"].toInt())+", "+json_obj["fname"].toString()+", "+json_obj["lname"].toString()+"\r";
    // }

    //ui->textCustomer->setText(customer);

    reply->deleteLater();
    getManager->deleteLater();
}

//POST SLOT
void CustomerTests::addCustomerSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}


//GET WITHRAWAL
void CustomerTests::getWithdrawalsInfo()
{
    QString site_url="http://localhost:3000/withdrawal/1";
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

    //Tässä kohtaa signaali käsittelevään hommaan mainissa
    emit withrawalsInfo(json_array);
    qDebug()<<json_array;

    reply->deleteLater();
    getManager->deleteLater();
}
