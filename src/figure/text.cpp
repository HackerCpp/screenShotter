#include "inc\figure\text.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Text::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Text::Text(int x,int y,int width, int height,QPen pen,int number):
m_number(number){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
}
/*void Text::setCursorP(QPointF pos){

}*/
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        //if(isActive){
        //}
        painter->setPen(*pen);
        painter->setBrush(*brush);
        //painter->drawRect(QRect(m_x,m_y,m_w,m_h));
}


void Text::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        //QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        //update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Text::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        //QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        //update();
    }
    /*if(isActive){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }*/
}
void Text::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    //update();
}
void Text::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Text::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Text::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
