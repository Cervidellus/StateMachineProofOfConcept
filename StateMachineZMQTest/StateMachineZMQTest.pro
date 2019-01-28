#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T18:58:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StateMachineZMQTest
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


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

STATECHARTS +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../vcpkg-master/installed/x64-windows/bin/ -llibzmq-mt-4_3_1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../vcpkg-master/installed/x64-windows/debug/bin/ -llibzmq-mt-gd-4_3_1

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../vcpkg-master/installed/x64-windows/lib/ -llibzmq-mt-4_3_1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../vcpkg-master/installed/x64-windows/debug/lib/ -llibzmq-mt-gd-4_3_1

INCLUDEPATH += $$PWD/../../../../../vcpkg-master/installed/x64-windows/include
DEPENDPATH += $$PWD/../../../../../vcpkg-master/installed/x64-windows/include


