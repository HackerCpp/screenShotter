#-------------------------------------------------
#
# Project created by QtCreator 2019-09-07T20:05:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = screenShot
TEMPLATE = app
INCLUDEPATH += $$PWD
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
        src/main.cpp \
        src/mainwindow.cpp \
    src/screenscene.cpp \
    src/panel.cpp \
    src/figure/curtain.cpp \
    src/figure/figure.cpp \
    src/figure/penandbrush.cpp\
src/figure/arrow.cpp\
src/figure/line.cpp\
src/figure/ellips.cpp\
src/figure/sepia.cpp\
src/figure/text.cpp\
    src/client.cpp \
    src/communicationwithserver.cpp

HEADERS += \
        inc/mainwindow.h \
    inc/screenscene.h \
    inc/panel.h \
    inc/figure/curtain.h \
    inc/figure/figure.h \
    inc/figure/penandbrush.h\
inc/figure/arrow.h\
inc/figure/line.h\
inc/figure/ellips.h\
inc/figure/sepia.h\
inc/figure/text.h\
    inc/client.h \
    inc/communicationwithserver.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
