#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include "rfid.h"
#include "pinui.h"
#include "logindll.h"
#include "welcome.h"
#include "accountinfo.h"
#include "cardselect.h"

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
    void setLoginStatus(LoginDLL::LoginStatus);
    void setAccount(QJsonObject);
    void logout();
    void openWithdraw();
    void getAccountNumber(QString);
    void openInfo();

private:
    Ui::mw1 *ui;
    QWidget *widget;
    RFID *cardReader;
    QString cardNumber;
    QString pin;
    LoginDLL *login;
    LoginDLL::LoginStatus loginStatus;
    QJsonObject account;
    bool initialization = true;
    int tries = 0;
    QString accountID;

    enum SelectWidget {
        WidgetWelcome,
        WidgetInfo,
        WidgetCardSelect,
        WidgetPinUI,
        WidgetWithdraw,
    };

    void setWidget(SelectWidget);
};
#endif // MW1_H
