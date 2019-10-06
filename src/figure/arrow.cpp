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
    if(tail){
        m_pointsBegin->data()[2].setY(length + heightmin);
        m_pointsBegin->data()[3].setY(length +heightmax);
        m_pointsBegin->data()[4].setY(length);
        m_pointsBegin->data()[5].setY(length +heightmax);
        m_pointsBegin->data()[6].setY(length+heightmin);

        m_pointsBegin->data()[0].setY(0);
        m_pointsBegin->data()[1].setY(0);
        m_translateY -= m_h;
        m_translateX -= m_w;
        tail = false;
    }
    double lengthA = qSqrt(qPow((0 + event->pos().x()-m_translateX),2)+qPow((0 + event->pos().y()-m_translateY),2));
    double lengthB = qSqrt(qPow(0 + (event->pos().x()-m_translateX),2)+qPow((lengthA + event->pos().y()-m_translateY ),2));
    double lengthC = qSqrt(qPow((0 + event->pos().x()-m_translateX),2)+qPow((0 + event->pos().y()-m_translateY),2));
    double cos = (qPow(lengthC,2)+qPow(lengthA,2) - qPow(lengthB,2))/(2*lengthC*lengthA);
    length = lengthA;
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
        m_pointsBegin->data()[2].setY(-lengthA + heightmin);
        m_pointsBegin->data()[3].setY(-lengthA +heightmax);
        m_pointsBegin->data()[4].setY(-lengthA);
        m_pointsBegin->data()[5].setY(-lengthA +heightmin);
        m_pointsBegin->data()[6].setY(-lengthA+heightmax);
        m_pointsBegin->data()[2].setX(widthmin);
        m_pointsBegin->data()[3].setX(-widthmax);
        m_pointsBegin->data()[5].setX(widthmax);
        m_pointsBegin->data()[6].setX(-widthmin);
    }
}
void Arrow::transformationTwo(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w += p.x();
    m_h += p.y();
    m_x -= p.x();
    m_y -= p.y();
    if(!tail){
        m_pointsBegin->data()[2].setY(0 + 14);
        m_pointsBegin->data()[3].setY(0 +15);
        m_pointsBegin->data()[4].setY(0);
        m_pointsBegin->data()[5].setY(0 +15);
        m_pointsBegin->data()[6].setY(0+14);

        m_pointsBegin->data()[0].setY(length);
        m_pointsBegin->data()[1].setY(length);
        m_translateY += m_h;
        m_translateX += m_w;
        tail = true;
    }
    double lengthA = qSqrt(qPow((0 + event->pos().x()-m_translateX),2)+qPow((0 + event->pos().y()-m_translateY),2));
    double lengthB = qSqrt(qPow(0 + (event->pos().x()-m_translateX),2)+qPow((lengthA + event->pos().y()-m_translateY ),2));
    double lengthC = qSqrt(qPow((0 + event->pos().x()-m_translateX),2)+qPow((0 + event->pos().y()-m_translateY),2));
    double cos = (qPow(lengthC,2)+qPow(lengthA,2) - qPow(lengthB,2))/(2*lengthC*lengthA);
    length = lengthA;
    if(event->pos().x()>m_translateX)
        m_angX = (qAcos(cos)*180)/3.14-180;
    else {
        m_angX = -(qAcos(cos)*180)/3.14-180;
    }
    m_pointsBegin->data()[0].setY(length);
    m_pointsBegin->data()[1].setY(length);

}
Arrow::Arrow(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    tail = false;
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
    widthmin = 5;widthmax = 10;
    heightmin = 14;
    heightmax = 15;
}
bool Arrow::isPointColor(QPoint p){
    QImage image(scene()->width(),scene()->height(), QImage::Format_RGB32);
    image.fill(nullptr);
    QPainter painter(&image);
    QPen pe(Qt::white);
    pe.setWidth(pen->width());
    painter.setPen(pe);
    painter.setBrush(QBrush(Qt::white));
    painter.translate(m_translateX,m_translateY);
    painter.rotate(m_angX);
    painter.drawPolygon(QPolygon(*m_pointsBegin));
    if(isActive){
      painter.drawEllipse(m_pointsBegin->data()[4].x()-5,m_pointsBegin->data()[4].y()-5,5,5);
      painter.drawEllipse(m_pointsBegin->data()[0].x()-5,m_pointsBegin->data()[0].x()-5,5,5);
      painter.drawLine(m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)-5,
                        m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)-5,
                        m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)+5,
                        m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)+5);
      painter.drawLine(m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)-5,
                        m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)+5,
                        m_pointsBegin->data()[4].x()+((m_pointsBegin->data()[0].x()-m_pointsBegin->data()[4].x())/2)+5,
                        m_pointsBegin->data()[4].y()+((m_pointsBegin->data()[0].y()-m_pointsBegin->data()[4].y())/2)-5);

    }
    QColor posColor = QColor(image.pixel(p.x(),p.y()));
    if (posColor == Qt::white){
         return true;
    }
    return false;
}
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    //painter->drawRect(boundingRect());
        painter->translate(m_translateX,m_translateY);
        painter->rotate(m_angX);
        brush->setColor(pen->color());
        pen->setWidth(2);
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawPolygon(QPolygon(*m_pointsBegin));
        if(isActive){
          painter->setPen(*penActive);
          painter->setBrush(*brushActive);
          painter->drawEllipse(m_pointsBegin->data()[4].x()-5,m_pointsBegin->data()[4].y()-5,5,5);
          painter->drawEllipse(m_pointsBegin->data()[0].x()-5,m_pointsBegin->data()[0].x()-5,5,5);
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
        for(int i_x = m_x-15;i_x < m_x+15;i_x++){
            for(int i_y =m_y- 15;i_y < m_y + 15;i_y++){
                if(i_x == event->pos().x() & i_y == event->pos().y()){
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
            transformationTwo(event);
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
