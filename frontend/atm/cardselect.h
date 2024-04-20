#ifndef CARDSELECT_H
#define CARDSELECT_H

#include <QWidget>
#include "logindll.h"

namespace Ui {
class CardSelect;
}

class CardSelect : public QWidget
{
    Q_OBJECT

public:
    explicit CardSelect(QWidget *parent = nullptr, LoginDLL *login = nullptr);
    ~CardSelect();

private:
    Ui::CardSelect *ui;
    LoginDLL *login;
    QJsonObject debit;
    QJsonObject credit;

private slots:
    void accountSelect(QJsonArray);
    void on_cardDebit_clicked();
    void on_cardCredit_clicked();

signals:
    void selectedAccount(QJsonObject);
};

#endif // CARDSELECT_H
