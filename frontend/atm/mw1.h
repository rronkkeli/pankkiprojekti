#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
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
    void setLoginStatus(LoginDLL::LoginStatus);

private:
    Ui::mw1 *ui;
    QWidget *widget;
    bool card_ins;
    RFID *cardReader;
    QString cardNumber;
    PinUI *pinUI;
    QString pin;
    void logout();
    LoginDLL *login;
    LoginDLL::LoginStatus loginStatus;

    enum SelectWidget {
        WidgetWelcome,
        WidgetInfo,
    };

    void setWidget(SelectWidget);
};
#endif // MW1_H
