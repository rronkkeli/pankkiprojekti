#include "rfid.h"
#include <QSerialPortInfo>

RFID::RFID(QObject *parent) : QObject(parent) {
    qDebug() << "Card reader class created";
    this->cardReader = new QSerialPort;
    this->setReader();

    connect(this->cardReader, SIGNAL(readyRead()), this, SLOT(readCard()));
}

RFID::~RFID() {
    this->cardReader->close();
    delete this->cardReader;
}

bool RFID::setReader() {
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    qsizetype length = availablePorts.length();
    qDebug() << "Ports available: " << length;

    for (qsizetype i = 0; i < length; i++) {
        qDebug() << "-----Port info-----";
        qDebug() << "Port name: " << availablePorts[i].portName()
                 << "\nSerial number: " << availablePorts[i].serialNumber()
                 << "\nVendor identifier: " << availablePorts[i].vendorIdentifier()
                 << "\nManufacturer: " << availablePorts[i].manufacturer()
                 << "\nDescription: " << availablePorts[i].description() << "\n";

        if (availablePorts[i].serialNumber() == QString("OL56DED005B8E88")) {
            this->cardReader->setPort(
                availablePorts[i]
            );

            qDebug() << "Card reader found. Port " << this->cardReader->portName() << " has been set";

            if (this->cardReader->open(QIODeviceBase::ReadOnly)) {
                qDebug() << "Opening reader was successful";
            } else if (this->cardReader->isOpen()) {
                return true;
            } else {
                qDebug() << "Opening reader " << this->cardReader->errorString() << " failed";
                return false;
            }

            return true;
        }
    }

    qDebug() << "No card reader available";
    return false;
}

void RFID::readCard() {
    QString cardData = QString::fromUtf8(this->cardReader->readAll()).sliced(3, 10);
    qDebug() << "A card was read by library. Emitting card data..";
    emit this->cardData(cardData);
    qDebug() << "Card data emitted";
}

