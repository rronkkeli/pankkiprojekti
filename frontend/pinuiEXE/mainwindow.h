#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pinui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonEXE_clicked();
    void handlePinNumberDLLSignal(QString);

private:
    Ui::MainWindow *ui;
    PinUI * ptr_dll;
};
#endif // MAINWINDOW_H
