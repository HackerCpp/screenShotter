#include "inc\figure\sepia.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QColor>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>

void Sepia::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Sepia::Sepia(int x,int y,int width, int height,QPen pen,QPixmap pixmap){
    m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    close = true;
    this->m_pixMap = pixmap;
    prevPoints = QPointF(x,y);
}
Q_GUI_EXPORT void qt_blurImage( QPainter* p, QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
void Sepia::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        int w,h,x,y;
        x = m_w < 0?m_x + m_w:m_x;
        w = m_w < 0?-m_w:m_w;
        y = m_h < 0?m_y + m_h:m_y;
        h = m_h < 0?-m_h:m_h;
        w = w?w:1;
        h = h?h:1;
        QImage img(this->m_pixMap.toImage().copy(x,y,w,h));
        painter->translate(x,y);
        qt_blurImage(painter, img, pen->width()+10, true, false );
        if(isActive){
          painter->setPen(*penActive);
          painter->setBrush(*brushActive);
          painter->drawEllipse(0,0,5,5);
          painter->drawEllipse(0+w/2,0,5,5);
          painter->drawEllipse(0,0+h/2,5,5);
          painter->drawEllipse(0+w/2,0+h/2,5,5);

          painter->drawEllipse(0+w/4,0,5,5);
          painter->drawEllipse(0+w/4,0+h/2,5,5);
          painter->drawEllipse(0,0+h/4,5,5);
          painter->drawEllipse(0+w/2,0+h/4,5,5);
        }

}


void Sepia::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Sepia::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
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
void Sepia::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        close = false;
        setZValue(4);
    }
    QGraphicsItem::prepareGeometryChange();
    update();
}
void Sepia::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Sepia::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Sepia::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
