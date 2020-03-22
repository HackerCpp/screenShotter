#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "inc/panel.h"
#include "inc/tabs/tabregistration.h"
#include "inc/tabs/tabgraphicseditor.h"
#include "inc/tabs/window.h"
#include "inc/tabs/menu.h"
#include <QShortcut>
#include "inc/hookkeybord.h"
#include "qxtglobalshortcut.h"
#include <QWidget>
#include <QTimer>

class MainWindow : public QWidget {
    Q_OBJECT
    QTimer *m_timer;
    HookKeybord *m_key;
    QxtGlobalShortcut *m_shortcutFullScrin,*m_shortcutPartScrin;
    TabGraphicsEditor *m_graphicsEditor;
    //Wind *m_wind;
    Menu *m_menu;
    TabRegistration * m_tabRegist;
    BtnsForUrl * m_btnForUrl;
    QRect m_size;
    Tray *m_trayIcon;
public:
    MainWindow();
    ~MainWindow();
public slots:
    void startHook();
    void openHistory();
    void startGraphicsEditFull();
    void startGraphicsEditPart();
    void programStart();
    void deleteGrapgicsEditor(bool isScreen);
    void deleteUrl();
    void quit();
   void hoock(HookKeybord::HookKey hoo);
   void partScreenHook();
   void fullScreenHook();

};

#endif // MAINWINDOW_H
