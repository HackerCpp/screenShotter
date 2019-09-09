#include "curtain.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Curtain::Curtain(int x,int y,int width, int height):
x(x),y(y),w(width),h(height){
    //setAcceptHoverEvents(true);
    isClose = 0;
}
QRectF Curtain::boundingRect() const{
    return QRectF(x, y, w, h);
}
void Curtain::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(!isClose){
        painter->setPen(QPen(QColor(0,0,0,150)));
        painter->setBrush(QBrush(QColor(0,0,0,150)));
        painter->drawRect(x,y,w,h);
        painter->setPen(QPen(Qt::white));
    }
    else{
        QPen pen(Qt::white);
        pen.setWidthF(0.25);
        painter->setPen(pen);
        painter->setBrush(QBrush(QColor(0,0,0,150)));
        painter->drawRect(QRect().adjusted(0,0,lUp.x(),lUp.y()));
        painter->drawRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()));
        painter->drawRect(QRect().adjusted(rUp.x(),0,w,rUp.y()));
        painter->drawRect(QRect().adjusted(rUp.x(),rUp.y(),w,rDown.y()));
        painter->drawRect(QRect().adjusted(rDown.x(),rDown.y(),w,h));
        painter->drawRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),h));
        painter->drawRect(QRect().adjusted(0,lDown.y(),lDown.x(),h));
        painter->drawRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()));
    }
}


void Curtain::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!isClose){
        isClose = 1;
        beginPoint = event->pos();
        lUp = lDown = rUp = rDown = event->pos();
    }
    else if (isClose == 1){
        isClose = 2;

    }
    else{
        prevPoint = event->pos();
    }
    update();
}
void Curtain::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(isClose == 1){
    if(event->pos().x() > beginPoint.x() & event->pos().y() > beginPoint.y()){
        lDown.setY(event->pos().y());
        rUp.setX(event->pos().x());
        rDown = event->pos();
    }
    else if(event->pos().x() < beginPoint.x() & event->pos().y() < beginPoint.y()){
        rUp.setY(event->pos().y());
        lDown.setX(event->pos().x());
        lUp = event->pos();
    }
    else if(event->pos().x() < beginPoint.x() & event->pos().y() > beginPoint.y()){
        rDown.setY(event->pos().y());
        lUp.setX(event->pos().x());
        lDown = event->pos();
    }
    else if(event->pos().x() > beginPoint.x() & event->pos().y() < beginPoint.y()){
        lUp.setY(event->pos().y());
        rDown.setX(event->pos().x());
        rUp = event->pos();
    }
    }
    else if(isClose == 2){
        QPointF p = prevPoint - event->pos();
        if(prevPoint.x() > rUp.x() & prevPoint.y() > rDown.y()){
            rDown-=p;
            rUp.setX(rUp.x()-p.x());
            lDown.setY(lDown.y()-p.y());
        }


        prevPoint = event->pos();
    }

    update();
}
void Curtain::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}
void Curtain::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Curtain::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

}
void Curtain::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){

}
