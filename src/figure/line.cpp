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
        pen->setCapStyle(Qt::RoundCap);
        //painter->translate(m_translateX,m_translateY);
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawLine(m_x,m_y,m_x+m_w,m_y+m_h);
        if(isActive){
          painter->setPen(*penActive);
          painter->setBrush(*brushActive);
          painter->drawEllipse(m_x-5,m_y-5,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y+m_h-5,10,10);
          painter->drawLine(m_x+m_w/2-5,m_y+m_h/2-5,m_x+m_w/2+5,m_y+m_h/2+5);
          painter->drawLine(m_x+m_w/2-5,m_y+m_h/2+5,m_x+m_w/2+5,m_y+m_h/2-5);
          //painter->drawRect(boundingRect());
        }
}


void Line::mousePressEvent(QGraphicsSceneMouseEvent *event){
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
        for(int i_x = m_x+m_w - 10;i_x<m_x+m_w+10;i_x++){
            for(int i_y =m_y+m_h-10;i_y < m_y+m_h+10;i_y++){
                if(i_x == event->pos().x() & i_y == event->pos().y()){
                    cursorPosition = 2;
                }
            }
        }
        for(int i_x = m_x - 10;i_x<m_x + 10;i_x++){
            for(int i_y =m_y - 10;i_y < m_y + 10;i_y++){
                if(i_x == event->pos().x() & i_y == event->pos().y()){
                    cursorPosition = 3;
                }
            }
        }
        prevPoints = event->scenePos();
    }
}
void Line::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        transformation(event);
        prevPoints = event->scenePos();
        QGraphicsItem::prepareGeometryChange();
        update();
    }
    if(isActive){
        if(cursorPosition == 1){
            m_x -= prevPoints.x() - event->pos().x();
            m_y -= prevPoints.y() - event->pos().y();
        }
        else if(cursorPosition == 2){
            QPointF p = prevPoints - event->scenePos();
            m_w -= p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 3){
            QPointF p = prevPoints - event->scenePos();
            m_x -= p.x();
            m_y -= p.y();
            m_w += p.x();
            m_h += p.y();
        }
        prevPoints = event->scenePos();
        QGraphicsItem::prepareGeometryChange();
        update();
    }
}
void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    cursorPosition = 0;
    QGraphicsItem::prepareGeometryChange();
    update();
}
void Line::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Line::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
