QT       += core gui \
            network \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountinfo.cpp \
    cardselect.cpp \
    main.cpp \
    mainwindow.cpp \
    welcome.cpp \
    withdraw.cpp

HEADERS += \
    accountinfo.h \
    cardselect.h \
    mainwindow.h \
    welcome.h \
    withdraw.h

FORMS += \
    accountinfo.ui \
    cardselect.ui \
    mainwindow.ui \
    welcome.ui \
    withdraw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    darkeum.qss


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../loginDLL/build/release/ -lloginDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../loginDLL/build/debug/ -lloginDLL

INCLUDEPATH += $$PWD/../loginDLL
DEPENDPATH += $$PWD/../loginDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../pinuiDLL/build/release/ -lpinuiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../pinuiDLL/build/debug/ -lpinuiDLL

INCLUDEPATH += $$PWD/../pinuiDLL
DEPENDPATH += $$PWD/../pinuiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../rfid/build/release/ -lrfid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../rfid/build/debug/ -lrfid

INCLUDEPATH += $$PWD/../rfid
DEPENDPATH += $$PWD/../rfid

RESOURCES += \
    res.qrc
