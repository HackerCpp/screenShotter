#include "panel.h"
#include <QMouseEvent>
#include <QPoint>
#include <QCoreApplication>

Panel::Panel(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool|Qt::WindowStaysOnTopHint);
    this->vBoxLayout = new QVBoxLayout();
    this->toolBar = new QToolBar();
    this->toolBar->addAction(QPixmap("panel\\pen"), "pen", this, SLOT(set()));
    toolBar->addSeparator();
    this->toolBar->addAction(QPixmap("panel\\brush"), "brush", this, SLOT(set()));
    toolBar->addSeparator();
    this->toolBar->addAction(QPixmap("panel\\square"), "rect", this, SLOT(set()));
    vBoxLayout->addWidget(toolBar);
    this->setLayout(vBoxLayout);
    active = false;
    this->setMaximumSize(200,50);
}

void Panel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        active = true;
        this->previousPoint = event->globalPos();
    }
}

void Panel::mouseMoveEvent(QMouseEvent *event){
    if(active){
            int dt = previousPoint.x() - event->globalX();
            QPoint d = previousPoint - event->globalPos();
            this->move(this->pos() - d);
    }
    this->previousPoint = event->globalPos();
}
void Panel::mouseReleaseEvent(QMouseEvent *event){
    active = false;
}
void Panel::set(){
    qApp->quit();
}
