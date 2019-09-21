#include "inc\figure\arrow.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QtMath>

void Arrow::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();

    double lengthA = qSqrt(qPow((0 + event->pos().x()-m_translateX),2)+qPow((0 + event->pos().y()-m_translateY),2));
    double lengthB = qSqrt(qPow(0 + (event->pos().x()-m_translateX),2)+qPow((lengthA + event->pos().y()-m_translateY ),2));
    double lengthC = qSqrt(qPow((0 + event->pos().x()-m_translateX),2)+qPow((0 + event->pos().y()-m_translateY),2));
    double cos = (qPow(lengthC,2)+qPow(lengthA,2) - qPow(lengthB,2))/(2*lengthC*lengthA);
    if(event->pos().x()>m_translateX)
        m_angX = (qAcos(cos)*180)/3.14;
    else {
        m_angX = -(qAcos(cos)*180)/3.14;
    }
    m_angY += p.y();
    if(qAbs(lengthA) < 15){
        m_pointsBegin->data()[2].setY(-lengthA);
        m_pointsBegin->data()[3].setY(-lengthA);
        m_pointsBegin->data()[4].setY(-lengthA);
        m_pointsBegin->data()[5].setY(-lengthA);
        m_pointsBegin->data()[6].setY(-lengthA);
        m_pointsBegin->data()[2].setX(lengthA);
        m_pointsBegin->data()[3].setX(-lengthA);

        m_pointsBegin->data()[5].setX(lengthA);
        m_pointsBegin->data()[6].setX(-lengthA);
    }
    else{
        m_pointsBegin->data()[2].setY(-lengthA + 14);
        m_pointsBegin->data()[3].setY(-lengthA +15);
        m_pointsBegin->data()[4].setY(-lengthA);
        m_pointsBegin->data()[5].setY(-lengthA +15);
        m_pointsBegin->data()[6].setY(-lengthA+14);
        m_pointsBegin->data()[2].setX(5);
        m_pointsBegin->data()[3].setX(-10);
        m_pointsBegin->data()[5].setX(10);
        m_pointsBegin->data()[6].setX(-5);
    }
}

Arrow::Arrow(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
    this->enableBrush();
    m_points = new QVector<QPoint>(7);
    length = 1;
    m_pointsBegin = new QVector<QPoint>(7);
    m_pointsBegin->data()[0] = QPoint(-2,0);
    m_pointsBegin->data()[1] = QPoint(2,0);
    m_pointsBegin->data()[2] = QPoint(0,-10);
    m_pointsBegin->data()[3] = QPoint(0,-10);
    m_pointsBegin->data()[4] = QPoint(0,0);
    m_pointsBegin->data()[5] = QPoint(0,-10);
    m_pointsBegin->data()[6] = QPoint(0,-10);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    //painter->drawRect(boundingRect());
        painter->translate(m_translateX,m_translateY);
        painter->rotate(m_angX);
        brush->setColor(pen->color());
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawPolygon(QPolygon(*m_pointsBegin));
        if(isActive){
          painter->setPen(*penActive);
          painter->setBrush(*brushActive);
          painter->drawEllipse(m_pointsBegin->data()[4].x()-5,m_pointsBegin->data()[4].y()-5,10,10);
          painter->drawEllipse(m_pointsBegin->data()[0].x()-5,m_pointsBegin->data()[0].x()-5,10,10);
          painter->drawLine(m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)-5,
                            m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)-5,
                            m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)+5,
                            m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)+5);
          painter->drawLine(m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)-5,
                            m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)+5,
                            m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)+5,
                            m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)-5);
        }
}


void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        int i = 0;
        m_translateX = event->pos().x();
        m_translateY = event->pos().y();
        m_x = m_translateX;
        m_y = m_translateY;
        for(auto pr = m_points->begin() ;pr < m_points->end();pr++ , i++){
            pr->setX(m_pointsBegin->at(i).x() * m_scaleX + m_translateX);
            pr->setY(m_pointsBegin->at(i).y() * m_scaleY + m_translateY);
        }
        update();
    }
    else{
        cursorPosition = 3;
        for(int i_x = m_x+m_w-15;i_x < m_x+m_w+15;i_x++){
            for(int i_y =m_y+m_h- 15;i_y < m_y+m_h + 15;i_y++){
                if(i_x == event->pos().x() & i_y == event->pos().y()){
                    cursorPosition = 1;
                }
            }
        }
        for(int i_x = m_pointsBegin->data()[0].x()-15;i_x < m_pointsBegin->data()[0].x()+5;i_x++){
            for(int i_y =m_pointsBegin->data()[0].y()- 15;i_y < m_pointsBegin->data()[0].y() + 5;i_y++){
                if(i_x == event->pos().x()-m_translateX & i_y == event->pos().y()-m_translateY){
                    cursorPosition = 2;
                }
            }
        }
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
        QPointF p = prevPoints - event->scenePos();
        QGraphicsItem::prepareGeometryChange();
        if(cursorPosition == 1){
            transformation(event);
        }
        else if(cursorPosition == 2){

        }
        else if(cursorPosition == 3){
            m_translateY-=p.y();
            m_translateX-=p.x();
            m_x -= p.x();
            m_y -= p.y();
        }

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
