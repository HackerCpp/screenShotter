#include "inc\figure\curtain.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

void Curtain::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Curtain::Curtain(int x,int y,int width, int height,QPen pen,int number):
m_number(number){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
}
bool Curtain::isPointColor(QPoint p){
    QImage image(scene()->width(),scene()->height(), QImage::Format_RGB32);
    image.fill(nullptr);
    QPainter painter(&image);
    QPen pe(Qt::white);
    pe.setWidth(pen->width());
    painter.setPen(pe);
    painter.drawRect(QRect(m_x,m_y,m_w,m_h));
    if(m_number){
        if(m_number < 10){
            painter.drawEllipse(QRect(m_x+m_w-6,m_y+m_h-6,12,12));
            painter.setPen(pen->color() == Qt::white?QPen(Qt::black):QPen(Qt::white));
            painter.drawText(m_x+m_w-3,m_y+m_h+5,QString::number(m_number));
         }
        else{
            painter.drawEllipse(QRect(m_x+m_w-8,m_y+m_h-8,15,15));
            painter.setPen(pen->color() == Qt::white?QPen(Qt::black):QPen(Qt::white));
            painter.drawText(m_x+m_w-7,m_y+m_h+5,QString::number(m_number));
        }

    }
    if(isActive){
      painter.drawEllipse(m_x-5,m_y-5,10,10);
      painter.drawEllipse(m_x+m_w-5,m_y-5,10,10);
      painter.drawEllipse(m_x-5,m_y+m_h-5,10,10);
      painter.drawEllipse(m_x+m_w-5,m_y+m_h-5,10,10);

      painter.drawEllipse(m_x+m_w/2,m_y-5,10,10);
      painter.drawEllipse(m_x+m_w/2,m_y+m_h-5,10,10);
      painter.drawEllipse(m_x-5,m_y+m_h/2,10,10);
      painter.drawEllipse(m_x+m_w-5,m_y+m_h/2,10,10);
      painter.drawLine(m_x+m_w/2-5,m_y+m_h/2-5,m_x+m_w/2+5,m_y+m_h/2+5);
      painter.drawLine(m_x+m_w/2-5,m_y+m_h/2+5,m_x+m_w/2+5,m_y+m_h/2-5);
    }
    QColor posColor = QColor(image.pixel(p.x(),p.y()));
    if (posColor == Qt::white){
         return true;
    }
    return false;
}
void Curtain::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){

        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->drawRect(QRect(m_x,m_y,m_w,m_h));
        if(m_number){
            painter->setBrush(QBrush(this->pen->color()));
            if(m_number < 10){
                painter->drawEllipse(QRect(m_x+m_w-6,m_y+m_h-6,12,12));
                painter->setPen(pen->color() == Qt::white?QPen(Qt::black):QPen(Qt::white));
                painter->drawText(m_x+m_w-3,m_y+m_h+5,QString::number(m_number));
             }
            else{
                painter->drawEllipse(QRect(m_x+m_w-8,m_y+m_h-8,15,15));
                painter->setPen(pen->color() == Qt::white?QPen(Qt::black):QPen(Qt::white));
                painter->drawText(m_x+m_w-7,m_y+m_h+5,QString::number(m_number));
            }

        }
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


void Curtain::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        cursorPosition = getPoint(event->pos());
        prevPoints = event->scenePos();
    }
}
void Curtain::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }
    if(isActive){
        QPointF p = prevPoints - event->scenePos();

        if(cursorPosition == 2){
            m_w -= p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 3){
            m_x -= p.x();
            m_y -= p.y();
            m_w += p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 4){
            m_y -= p.y();
            m_w -= p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 5){
            m_x -= p.x();
            m_w += p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 6){
            m_h += p.y();
            m_y -= p.y();
        }
        else if(cursorPosition == 7){
            m_h -= p.y();
        }
        else if(cursorPosition == 8){
            m_w += p.x();
            m_x -= p.x();
        }
        else if(cursorPosition == 9){
            m_w -= p.x();
        }
        else{
            m_x -= p.x();
            m_y -= p.y();
        }
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
}
void Curtain::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    cursorPosition = 0;
    QGraphicsItem::prepareGeometryChange();
    update();
}
void Curtain::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Curtain::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Curtain::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
