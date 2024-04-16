#include "accountinfo.h"
#include "ui_accountinfo.h"

AccountInfo::AccountInfo(QWidget *parent, LoginDLL *login)
    : QWidget(parent)
    , ui(new Ui::AccountInfo)
{
    ui->setupUi(this);

    connect(
        login,
        SIGNAL(tilitjakortitInfo(QJsonArray)),
        this,
        SLOT(getAccountInfo(QJsonArray))
    );

    this->login = login;
}

AccountInfo::~AccountInfo()
{
    delete ui;
    delete login;
}

void AccountInfo::getAccountInfo(QJsonArray accountInfo)
{
    qDebug() << "Account info: " << accountInfo;
}
