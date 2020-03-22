#include "inc/panel/btntooltip.h"
#include <QEvent>
#include <QDebug>
#include <QHelpEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QTextOption>

ToolTip::ToolTip(QWidget *parent):QWidget(parent){
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}
void ToolTip::paintEvent(QPaintEvent *event){
    QPolygon poligon;
    poligon << QPoint(20,height() - 5) << QPoint(30,height() - 5) << QPoint(25,height());
    QPainter p(this);
    //p.setPen(QPen(QColor(127,127,127,255)));
    p.setBrush(QBrush(QColor(0,0,0,200)));
    p.drawRect(0,0,width()-1,height() - 5);
    p.drawPolygon(poligon);
    p.setPen(QPen(Qt::white,4));
    p.setFont(QFont("Arial", 14));
    p.drawText(QRect(0,0,width(),height() - 5),"Всплывающая подсказка",QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
}
void BtnToolTip::showToolTip(){
    emit showToolTipP(mapToGlobal(QPoint(0,0)) - QPoint(0,60),m_index);
}
BtnToolTip::BtnToolTip(int index):m_index(index){
    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&BtnToolTip::showToolTip);
}
bool BtnToolTip::event(QEvent *e){
    QPushButton::event(e);
    if(e->type() == QEvent::ToolTip){
        m_timer->start(1);
        return false;
    }
    else {
        m_timer->stop();
        emit hideToolTipP();
    }

    return false;
}
BtnToolTip::~BtnToolTip(){
}
