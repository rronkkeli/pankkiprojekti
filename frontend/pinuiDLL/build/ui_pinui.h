/********************************************************************************
** Form generated from reading UI file 'pinui.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINUI_H
#define UI_PINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PinUI
{
public:
    QPushButton *btnPin2;
    QPushButton *btnPin7;
    QPushButton *btnPin8;
    QPushButton *btnPinEnter;
    QPushButton *btnPin1;
    QPushButton *btnPin6;
    QPushButton *btnPin9;
    QPushButton *btnPin5;
    QLineEdit *pinLineEdit;
    QPushButton *btnPin3;
    QPushButton *btnPinClear;
    QPushButton *btnPin4;
    QPushButton *btnPin0;

    void setupUi(QDialog *PinUI)
    {
        if (PinUI->objectName().isEmpty())
            PinUI->setObjectName("PinUI");
        PinUI->resize(400, 300);
        btnPin2 = new QPushButton(PinUI);
        btnPin2->setObjectName("btnPin2");
        btnPin2->setGeometry(QRect(160, 180, 80, 24));
        btnPin7 = new QPushButton(PinUI);
        btnPin7->setObjectName("btnPin7");
        btnPin7->setGeometry(QRect(60, 100, 80, 24));
        btnPin8 = new QPushButton(PinUI);
        btnPin8->setObjectName("btnPin8");
        btnPin8->setGeometry(QRect(160, 100, 80, 24));
        btnPinEnter = new QPushButton(PinUI);
        btnPinEnter->setObjectName("btnPinEnter");
        btnPinEnter->setGeometry(QRect(260, 220, 80, 24));
        btnPin1 = new QPushButton(PinUI);
        btnPin1->setObjectName("btnPin1");
        btnPin1->setGeometry(QRect(60, 180, 80, 24));
        btnPin6 = new QPushButton(PinUI);
        btnPin6->setObjectName("btnPin6");
        btnPin6->setGeometry(QRect(260, 140, 80, 24));
        btnPin9 = new QPushButton(PinUI);
        btnPin9->setObjectName("btnPin9");
        btnPin9->setGeometry(QRect(260, 100, 80, 24));
        btnPin5 = new QPushButton(PinUI);
        btnPin5->setObjectName("btnPin5");
        btnPin5->setGeometry(QRect(160, 140, 80, 24));
        pinLineEdit = new QLineEdit(PinUI);
        pinLineEdit->setObjectName("pinLineEdit");
        pinLineEdit->setGeometry(QRect(60, 53, 281, 31));
        btnPin3 = new QPushButton(PinUI);
        btnPin3->setObjectName("btnPin3");
        btnPin3->setGeometry(QRect(260, 180, 80, 24));
        btnPinClear = new QPushButton(PinUI);
        btnPinClear->setObjectName("btnPinClear");
        btnPinClear->setGeometry(QRect(160, 220, 80, 24));
        btnPin4 = new QPushButton(PinUI);
        btnPin4->setObjectName("btnPin4");
        btnPin4->setGeometry(QRect(60, 140, 80, 24));
        btnPin0 = new QPushButton(PinUI);
        btnPin0->setObjectName("btnPin0");
        btnPin0->setGeometry(QRect(60, 220, 80, 24));

        retranslateUi(PinUI);

        QMetaObject::connectSlotsByName(PinUI);
    } // setupUi

    void retranslateUi(QDialog *PinUI)
    {
        PinUI->setWindowTitle(QCoreApplication::translate("PinUI", "Dialog", nullptr));
        btnPin2->setText(QCoreApplication::translate("PinUI", "2", nullptr));
        btnPin7->setText(QCoreApplication::translate("PinUI", "7", nullptr));
        btnPin8->setText(QCoreApplication::translate("PinUI", "8", nullptr));
        btnPinEnter->setText(QCoreApplication::translate("PinUI", "ENTER", nullptr));
        btnPin1->setText(QCoreApplication::translate("PinUI", "1", nullptr));
        btnPin6->setText(QCoreApplication::translate("PinUI", "6", nullptr));
        btnPin9->setText(QCoreApplication::translate("PinUI", "9", nullptr));
        btnPin5->setText(QCoreApplication::translate("PinUI", "5", nullptr));
        btnPin3->setText(QCoreApplication::translate("PinUI", "3", nullptr));
        btnPinClear->setText(QCoreApplication::translate("PinUI", "CLEAR", nullptr));
        btnPin4->setText(QCoreApplication::translate("PinUI", "4", nullptr));
        btnPin0->setText(QCoreApplication::translate("PinUI", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PinUI: public Ui_PinUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINUI_H
