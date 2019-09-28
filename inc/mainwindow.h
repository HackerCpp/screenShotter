#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "inc/panel.h"
#include "inc/tabs/tabregistration.h"
#include "inc/tabs/tabgraphicseditor.h"

class MainWindow : public QObject {
    Q_OBJECT
    TabGraphicsEditor *m_graphicsEditor;
    Wind *m_wind;
    TabRegistration * m_tabRegist;
public:
    MainWindow();
    ~MainWindow();

public slots:
    void openUrl();
    void copyUrl();
    void startGraphicsEditFull();
    void startGraphicsEditPart();
    void programStart();
    void deleteGrapgicsEditor();

};

#endif // MAINWINDOW_H
