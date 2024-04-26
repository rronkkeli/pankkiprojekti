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
    explicit CardSelect(QWidget *parent = nullptr);
    ~CardSelect();

    enum AccountType {
        Debit,
        Credit,
        Unset
    };

    // Unsets type
    void zeroize();

private:
    Ui::CardSelect *ui;
    AccountType type;

private slots:
    void accountSelect();

signals:
    void selectedAccount(AccountType);
};

#endif // CARDSELECT_H
