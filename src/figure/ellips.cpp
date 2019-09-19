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
        pen->setCapStyle(Qt::RoundCap);
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawEllipse(m_x,m_y,m_w,m_h);
        if(isActive){
          painter->setPen(*penActive);
          painter->setBrush(*brushActive);
          painter->drawEllipse(m_x-5,m_y-5,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y-5,10,10);
          painter->drawEllipse(m_x-5,m_y+m_h-5,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y+m_h-5,10,10);

          painter->drawEllipse(m_x+m_w/2,m_y-5,10,10);
          painter->drawEllipse(m_x+m_w/2,m_y+m_h-5,10,10);
          painter->drawEllipse(m_x-5,m_y+m_h/2,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y+m_h/2,10,10);
          painter->drawLine(m_x+m_w/2-5,m_y+m_h/2-5,m_x+m_w/2+5,m_y+m_h/2+5);
          painter->drawLine(m_x+m_w/2-5,m_y+m_h/2+5,m_x+m_w/2+5,m_y+m_h/2-5);
        }
}


void Ellips::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        for(int i_x = m_x+m_w/2 - 10;i_x<m_x+m_w/2+10;i_x++){
            for(int i_y =m_y+m_h/2-10;i_y < m_y+m_h/2+10;i_y++){
                if(i_x == event->pos().x() & i_y == event->pos().y()){
                    cursorPosition = 1;
                }
            }
        }
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
        if(cursorPosition == 1){
            m_x -= prevPoints.x() - event->pos().x();
            m_y -= prevPoints.y() - event->pos().y();
        }
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
}
void Ellips::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    cursorPosition = 0;
    update();
}
void Ellips::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Ellips::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Ellips::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
