#include "inc\figure\line.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Line::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Line::Line(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
    this->enableBrush();
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){
        }
        pen->setCapStyle(Qt::RoundCap);
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawLine(m_x,m_y,m_x+m_w,m_y+m_h);
}


void Line::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Line::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
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
void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void Line::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Line::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
