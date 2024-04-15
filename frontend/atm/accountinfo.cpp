#include "accountinfo.h"
#include "ui_accountinfo.h"

AccountInfo::AccountInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountInfo)
{
    ui->setupUi(this);
    libCustomer = new CustomerTests(this);

    connect(
        libCustomer,
        SIGNAL(tilitjakortitInfo(QString,QString)),
        this,
        SLOT(getAccountInfo(QString,QString))
    );

    libCustomer->setAsiakas("1");
    libCustomer->getTilitjaKortitInfo();
}

AccountInfo::~AccountInfo()
{
    delete ui;
    delete libCustomer;
}

void AccountInfo::getAccountInfo(QString accounts, QString cards)
{
    QStringList accountsPieces = accounts.split(" \n", Qt::SkipEmptyParts);
    qsizetype length = accountsPieces.length();
    qDebug() << accountsPieces;

    if (length > 1) {

        QStringList fields = accountsPieces[1].split(" | ", Qt::SkipEmptyParts);
        ui->accountNumber->setText(fields[0]);

        account = fields[0];
        qint64 credit;

        if (fields.length() < 3) {
            credit = 0;
        } else {
            qint64 credit = fields[2].toInt();
        }

        if (credit > 0) {
            fields[2].append(" (luotto)");
            ui->accountBalance->setText(fields[2]);
        } else {
            fields[1].removeLast();
            ui->accountBalance->setText(fields[1]);
        }

    }

    qDebug() << libCustomer->getAsiakas();
}
