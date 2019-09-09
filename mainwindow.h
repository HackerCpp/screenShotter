#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "screenscene.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT
    ScreenScene *scene;



public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
