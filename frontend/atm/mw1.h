#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include <QStackedWidget>
#include "rfid.h"
#include "pinui.h"
#include "logindll.h"
#include "welcome.h"
#include "accountinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class mw1;
}
QT_END_NAMESPACE

class mw1 : public QMainWindow
{
    Q_OBJECT

public:
    mw1(QWidget *parent = nullptr);
    ~mw1();

private slots:
    void fetch_card_data();
    void set_pin(QString);
    void setLoginStatus(QString);

private:
    Ui::mw1 *ui;
    QWidget *widget;
    // QWidget *welcome;
    // QWidget *info;
    bool card_ins;
    RFID *cardReader;
    QString cardNumber;
    PinUI *pinUI;
    QString pin;
    void logout();
    LoginDLL *login;
    QString loginStatus;

    void setWidget(int);
};
#endif // MW1_H
