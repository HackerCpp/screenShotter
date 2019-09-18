#include "inc\figure\Win.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Win::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Win::Win(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
}

void Win::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){

        }
        painter->drawRect(QRect(m_x,m_y,m_w,m_h));
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawRect(QRect(m_x,m_y,m_w,m_h));

}


void Win::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Win::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
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
void Win::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void Win::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Win::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Win::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
