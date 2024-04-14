#include "logindll.h"

LoginDLL::LoginDLL(QObject * parent):QObject(parent) {

}

LoginDLL::~LoginDLL()
{

}

void LoginDLL::login(QString cardId, QString cardPin)
{
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

void LoginDLL::loginSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    QString status;
    qDebug()<<response_data;
    //Show user what the response is and send info to main program for message boxes
    if(response_data =="-4078") {
        //No database connection
        status = "Virhe tietokantayhteydessä";
        emit loginStatus(status);
    }
    else if(response_data != "false") {
        //Success
        status = "success";
        emit loginStatus(status);
    } else {
        //Wrong card num or pin
        status = "Kortin numero tai pin ei täsmää.";
        emit loginStatus(status);
    }
}
