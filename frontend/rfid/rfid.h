#ifndef RFID_H
#define RFID_H
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QObject>
#include "rfid_global.h"

class RFID_EXPORT RFID : public QObject {
    Q_OBJECT

private:
    QSerialPort *cardReader;

public:
    explicit RFID(QObject*);
    ~RFID();
    bool setReader();
    void closeReader();

private slots:
    void readCard();

signals:
    void cardData(QString);
};

#endif // RFID_H
