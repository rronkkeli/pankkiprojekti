QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountinfo.cpp \
    dialog.cpp \
    main.cpp \
    mw1.cpp \
    welcome.cpp

HEADERS += \
    accountinfo.h \
    dialog.h \
    mw1.h \
    welcome.h

FORMS += \
    accountinfo.ui \
    dialog.ui \
    mw1.ui \
    welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-rfid-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/release/ -lrfid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-rfid-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/debug/ -lrfid

INCLUDEPATH += $$PWD/../rfid
DEPENDPATH += $$PWD/../rfid

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-pinuiDLL-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/release/ -lpinuiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-pinuiDLL-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/debug/ -lpinuiDLL

INCLUDEPATH += $$PWD/../pinuiDLL
DEPENDPATH += $$PWD/../pinuiDLL

DISTFILES += \
    style.qss

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-loginDLL-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/release/ -lloginDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-loginDLL-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/debug/ -lloginDLL

INCLUDEPATH += $$PWD/../loginDLL
DEPENDPATH += $$PWD/../loginDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-customerTests-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/release/ -lcustomerTests
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-customerTests-Desktop_Qt_6_6_3_MinGW_64_bit-Debug/debug/ -lcustomerTests

INCLUDEPATH += $$PWD/../customerTests
DEPENDPATH += $$PWD/../customerTests
