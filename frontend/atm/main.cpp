#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString path = "darkeum.qss"; //Asetetaan oikea tyylitiedosto
    qDebug() << "Current path of style is: " << path;

    QFile stylesheet(path);
    if (stylesheet.open(QFile::ReadOnly)) {
        qDebug() << "Stylesheet opened";
    }

    QString styledata = QLatin1String(stylesheet.readAll());

    a.setStyleSheet(styledata);
    MainWindow w;
    w.show();
    return a.exec();
}


