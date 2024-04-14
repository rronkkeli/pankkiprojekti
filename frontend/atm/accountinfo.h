#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>

namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AccountInfo(QWidget *parent = nullptr);
    ~AccountInfo();

private:
    Ui::AccountInfo *ui;
};

#endif // ACCOUNTINFO_H
