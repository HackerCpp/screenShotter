#include "mainwindow.h"
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
    scene = new ScreenScene;
    this->setScene(scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->cursor().setPos(scene->width()/2,scene->height()/2);
    this->showFullScreen();
}

MainWindow::~MainWindow()
{

}
