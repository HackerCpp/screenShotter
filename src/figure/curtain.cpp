#include "inc\figure\curtain.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Curtain::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Curtain::Curtain(int x,int y,int width, int height,QPen pen,int number):
m_number(number){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
}

void Curtain::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){
          painter->setPen(QPen(Qt::green));
          painter->drawRect(QRect(m_x,m_y,100,100));
          painter->drawRect(QRect(m_x,m_y,99,100));
          painter->drawRect(QRect(m_x,m_y,98,100));
          painter->drawRect(QRect(m_x,m_y,97,100));
          painter->drawRect(QRect(m_x,m_y,96,100));
          painter->drawRect(QRect(m_x,m_y,95,100));
          painter->drawRect(QRect(m_x,m_y,94,100));
          painter->drawRect(QRect(m_x,m_y,93,100));
        }
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawRect(QRect(m_x,m_y,m_w,m_h));
        if(m_number){
            painter->setBrush(QBrush(this->pen->color()));
            if(m_number < 10){
                painter->drawEllipse(QRect(m_x+m_w-6,m_y+m_h-6,12,12));
                painter->setPen(QPen(Qt::white));
                painter->drawText(m_x+m_w-3,m_y+m_h+5,QString::number(m_number));
             }
            else{
                painter->drawEllipse(QRect(m_x+m_w-8,m_y+m_h-8,15,15));
                painter->setPen(QPen(Qt::white));
                painter->drawText(m_x+m_w-7,m_y+m_h+5,QString::number(m_number));
            }

        }
}


void Curtain::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Curtain::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }
    if(isActive){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }
}
void Curtain::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void Curtain::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Curtain::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Curtain::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
