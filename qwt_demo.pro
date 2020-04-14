#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T18:56:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qwt_demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    plot.cpp

HEADERS += \
        mainwindow.h \
    datadefine.h \
    plot.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LC:/doppSDK/Qwt-6.1.4/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/doppSDK/Qwt-6.1.4/lib/ -lqwtd
else:unix: LIBS += -LC:/doppSDK/Qwt-6.1.4/lib/ -lqwt

INCLUDEPATH += C:/doppSDK/Qwt-6.1.4/include
DEPENDPATH += C:/doppSDK/Qwt-6.1.4/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += C:/doppSDK/Qwt-6.1.4/lib/libqwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += C:/doppSDK/Qwt-6.1.4/lib/libqwtd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += C:/doppSDK/Qwt-6.1.4/lib/qwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += C:/doppSDK/Qwt-6.1.4/lib/qwtd.lib
else:unix: PRE_TARGETDEPS += C:/doppSDK/Qwt-6.1.4/lib/libqwt.a
