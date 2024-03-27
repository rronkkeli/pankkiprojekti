#ifndef RFID_H
#define RFID_H
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QObject>
#include "rfid_global.h"

class RFID_EXPORT RFID : public QObject {
    Q_OBJECT

private:
    QString cardData;

public:
    explicit RFID(QObject*);
    ~RFID();
    bool setReader();
    QSerialPort *cardReader;
    QString getCardData();

private slots:
    void readCard();

signals:
    void cardDataReady();
};

#endif // RFID_H
