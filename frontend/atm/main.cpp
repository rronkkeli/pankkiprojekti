#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString path1 = QDir::currentPath();
    QDir directory(path1);
    directory.cdUp();

    QString path2 = directory.filePath("darkeum.qss");
    qDebug() << "Current path of style is: " << path2;

    QFile stylesheet(path2);
    if (stylesheet.open(QFile::ReadOnly)) {
        qDebug() << "Stylesheet opened";
    }

    QString styledata = QLatin1String(stylesheet.readAll());

    a.setStyleSheet(styledata);
    MainWindow w;
    w.show();
    return a.exec();
}
