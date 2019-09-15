#include "inc\figure\arrow.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Arrow::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();

    points->data()[3] = QPoint(m_x+m_w,m_y+m_h);
    points->data()[4] = QPoint(m_x+m_w,m_y+m_h);

    //points->data()[1] = QPoint(event->pos().x(),m_y+m_h);
    //points->data()[2] = QPoint(m_x+m_w,m_y+m_h);
    //points->data()[5] = QPoint(m_x+m_w,m_y+m_h);
    //points->data()[6] = QPoint(m_x+m_w,m_y+m_h);
}

Arrow::Arrow(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
    this->enableBrush();
    points = new QVector<QPoint>(7);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){
        }
        brush->setColor(pen->color());
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawPolygon(QPolygon(*points));
}


void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        points->data()[0] = QPoint(event->scenePos().x(),event->scenePos().y());
        points->data()[1] = QPoint(event->scenePos().x()-10,event->scenePos().y()-10);
        points->data()[2] = QPoint(event->scenePos().x()-5,event->scenePos().y()-10);
        points->data()[3] = QPoint(m_x+m_w,m_y+m_h);
        points->data()[4] = QPoint(m_x+m_w,m_y+m_h);
        points->data()[5] = QPoint(event->scenePos().x()+5,event->scenePos().y()-10);
        points->data()[6] = QPoint(event->scenePos().x()+10,event->scenePos().y()-10);
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
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
void Arrow::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void Arrow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Arrow::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Arrow::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
