#include "inc\figure\Ellips.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Ellips::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Ellips::Ellips(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
}

void Ellips::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){
        }
        pen->setCapStyle(Qt::RoundCap);
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawEllipse(m_x,m_y,m_w,m_h);
}


void Ellips::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Ellips::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
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
void Ellips::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void Ellips::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Ellips::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Ellips::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}