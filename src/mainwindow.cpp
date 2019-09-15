#include "inc\mainwindow.h"
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "inc\panel.h"


MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
    Wind *wind = new Wind();
    scene = new ScreenScene;
    this->setScene(scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->cursor().setPos(scene->width()/2,scene->height()/2);
    this->showFullScreen();
    connect(scene->getPanel(),SIGNAL(enterBtn()),wind,SLOT(showWin()));
    connect(scene->getPanel(),SIGNAL(enterBtn()),this,SLOT(hideCitrain()));
}
void MainWindow::hideCitrain(){
    delete this->scene;
    this->hide();
}
MainWindow::~MainWindow()
{

}
