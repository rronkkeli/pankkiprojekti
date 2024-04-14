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

private slots:
    void on_pushButton_clicked();

private:
    Ui::Welcome *ui;

signals:
    void clicked();
};

#endif // WELCOME_H
