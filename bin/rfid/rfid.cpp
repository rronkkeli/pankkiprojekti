#include "rfid.h"
#include <QSerialPortInfo>

RFID::RFID() {
    qDebug() << "Card reader class created";
}

RFID::~RFID()
{

}

unsigned int RFID::getCardInfo() {
    return this->cardInfo;
    this->cardReader.setReadBufferSize(4);
}

void RFID::readCard() {
    // Read card and set it into this->cardInfo
    this->cardInfo = this->cardReader.readAll().toUInt();
}

void RFID::setReader() {
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    foreach (port, &availablePorts) {
        qDebug() << port;
    }
    // availablePorts.clear();
}
