#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T16:32:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatClient
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
        widget.cpp \
    xclienttcpsocket.cpp \
    xclientudpsocket.cpp \
    loginwindow.cpp \
    signupwindow.cpp \
    foundaccountwindow.cpp \
    message.cpp \
    userwindow.cpp \
    tcpserver.cpp \
    worker.cpp \
    chatwindow.cpp \
    filewindow.cpp \
    udppkt.cpp \
    urtreceiver.cpp \
    urtsender.cpp

HEADERS += \
        widget.h \
    xclienttcpsocket.h \
    xclientudpsocket.h \
    loginwindow.h \
    signupwindow.h \
    foundaccountwindow.h \
    message.h \
    userwindow.h \
    tcpserver.h \
    worker.h \
    chatwindow.h \
    filewindow.h \
    udppkt.h \
    urtreceiver.h \
    urtsender.h

FORMS += \
        widget.ui \
    loginwindow.ui \
    signupwindow.ui \
    foundaccountwindow.ui \
    message.ui \
    userwindow.ui \
    chatwindow.ui \
    filewindow.ui
