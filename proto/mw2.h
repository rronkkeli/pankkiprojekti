#ifndef MW2_H
#define MW2_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class mw1;
}
QT_END_NAMESPACE

class mw2 : public QWidget
{
    Q_OBJECT
public:
    explicit mw2(QWidget *parent = nullptr);

signals:
};

#endif // MW2_H
