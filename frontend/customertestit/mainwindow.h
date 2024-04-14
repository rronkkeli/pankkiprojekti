#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "customerTests.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;

    CustomerTests *ptr_dll;

private slots:

    void handleGottenInformation(QString customer);
    void handlewithdrawals (QString tilitiedot);
    void handlekortit(QString tilit, QString kortit);
    void handlenostoInfo(QString);

    void on_btnCustomerInfo_clicked();
    void on_btnWithdrawalsInfo_clicked();
    void on_btnkortitInfo_clicked();

    void on_btnPost_clicked();
    void on_btnNostotapahtuma_clicked();
};
#endif // MAINWINDOW_H
