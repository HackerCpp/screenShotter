#-------------------------------------------------
#
# Project created by QtCreator 2019-09-07T20:05:11
#
#-------------------------------------------------
! include( ./globalShortCut_lib/qxt.pri ) {
    error( "Couldn't find the qxt.pri file!" )
}
! include(./updater/QSimpleUpdater.pri) {
    error( "Couldn't find the qxt.pri file!" )
}
QT       += core gui network widgets
#LIBS+=-Wl,-rpath ./lib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent

TARGET = screenShot
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
    src/figure/arrow.cpp \
    src/figure/curtain.cpp \
    src/figure/ellips.cpp \
    src/figure/figure.cpp \
    src/figure/line.cpp \
    src/figure/penandbrush.cpp \
    src/figure/sepia.cpp \
    src/figure/text.cpp \
    src/panel/baseslider.cpp \
    src/panel/btn.cpp \
    src/panel/btninsert.cpp \
    src/panel/btnMnu.cpp \
    src/panel/btntooltip.cpp \
    src/panel/slidercolor.cpp \
    src/panel/slidersize.cpp \
    src/settings/activewindow.cpp \
    src/settings/settingtab.cpp \
    src/tabs/btnsforurl.cpp \
    src/tabs/menu.cpp \
src/tabs/contextmenu.cpp \
    src/tabs/tabbase.cpp \
    src/tabs/tabgraphicseditor.cpp \
    src/tabs/tabregistration.cpp \
    src/tabs/tabsettings.cpp \
    src/tabs/tray.cpp \
    src/tabs/window.cpp \
    src/client.cpp \
    src/communicationwithserver.cpp \
    src/hookkeybord.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/panel.cpp \
    src/screenscene.cpp \
    src/settings/autoplay.cpp \
    src/settings/hotkeytab.cpp \
    src/tabs/dialogforenterpathforsavescreenshot.cpp \
    src/tabs/btnsokandcansel.cpp

HEADERS += \
        inc/mainwindow.h \
    inc/panel/btninsert.h \
    inc/settings/settingtab.h \
    inc/screenscene.h \
inc/hookkeybord.h\
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
    inc/communicationwithserver.h \
    inc/tabs/tabregistration.h \
    inc/tabs/tabgraphicseditor.h \
    inc/tabs/window.h \
    inc/tabs/tabsettings.h \
    inc/tabs/tabbase.h \
    inc/tabs/btnsforurl.h \
    inc/tabs/tray.h \
    inc/tabs/contextmenu.h \
    inc/tabs/menu.h \
    inc/panel/btn.h \
inc/panel/btnMnu.h \
    inc/panel/baseslider.h \
    inc/panel/slidercolor.h \
    inc/panel/slidersize.h \
    inc/panel/btntooltip.h \
    inc/settings/autoplay.h \
    inc/settings/hotkeytab.h \
    inc/tabs/dialogforenterpathforsavescreenshot.h \
    inc/tabs/btnsokandcansel.h \
    inc/settings/activewindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

FORMS += \
    hotkey.ui
