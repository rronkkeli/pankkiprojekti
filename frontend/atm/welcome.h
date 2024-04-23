#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>

namespace Ui {
class Welcome;
}

class Welcome : public QWidget
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome();
    void setStart();
    void setReadCard();
    void setCardReaderError();

private:
    Ui::Welcome *ui;

signals:
    void start();

private slots:
    void on_pbstart_clicked();
    void on_pbok_clicked();
};

#endif // WELCOME_H
