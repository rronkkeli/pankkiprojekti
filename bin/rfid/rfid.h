#ifndef RFID_H
#define RFID_H
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include "rfid_global.h"

class RFID_EXPORT RFID
{
    unsigned int cardInfo;
    QSerialPort cardReader;

public:
    RFID();
    ~RFID();
    unsigned int getCardInfo();
    void readCard();
    void setReader();
};

#endif // RFID_H
